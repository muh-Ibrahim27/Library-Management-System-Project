#include <iostream>
#include<cstring>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;
const int TITLE_LENGTH = 100;
const int AUTHOR_LENGTH = 50;
const int MAX_USERS = 50;
const int NAME_LENGTH = 50;

struct Book
{
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    bool isAvailable;
};

struct User
{
    int id;
    char name[NAME_LENGTH];
    int borrowedBookId;
};

void addBook(Book* books, int* bookCount);
void displayBooks(const Book* books, int bookCount);
void borrowBook(Book* books, int bookCount, User* users, int userCount);
void returnBook(Book* books, int bookCount, User* users, int userCount);
void searchBook(const Book* books, int bookCount);
void addUser(User* users, int* userCount);
void displayUsers(const User* users, int userCount);

int main()
{
    Book books[MAX_BOOKS];
    User users[MAX_USERS];
    int bookCount = 0;
    int userCount = 0;
    int choice;

    cout << "-----------------------------------------" << endl;
    cout << "*****Final Project*****" << endl;
    cout << "*Library Management System*" << endl;

    while (true)
    {
        cout << "-----------------------------------------" << endl;
        cout << "Please choose an operation:" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Search Book" << endl;
        cout << "6. Add User" << endl;
        cout << "7. Display Users" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cout << "-----------------------------------------" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook(books, &bookCount);
            break;
        case 2:
            displayBooks(books, bookCount);
            break;
        case 3:
            borrowBook(books, bookCount, users, userCount);
            break;
        case 4:
            returnBook(books, bookCount, users, userCount);
            break;
        case 5:
            searchBook(books, bookCount);
            break;
        case 6:
            addUser(users, &userCount);
            break;
        case 7:
            displayUsers(users, userCount);
            break;
        case 8:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void addBook(Book* books, int* bookCount)
{
    if (*bookCount >= MAX_BOOKS)
    {
        cout << "Library space is full. Cannot add more books." << endl;
        return;
    }


    cout << "Enter title: ";
    cin.ignore();
    cin.getline(books[*bookCount].title, TITLE_LENGTH);
    cout << "Enter author: ";
    cin.getline(books[*bookCount].author, AUTHOR_LENGTH);
    books[*bookCount].id = *bookCount + 1;
    books[*bookCount].isAvailable = true;

    (*bookCount)++;
    cout << "Book added successfully!" << endl;
}


void displayBooks(const Book* books, int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books in the library." << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++)
    {
        cout << "ID: " << books[i].id << endl;
        cout << "Title: " << books[i].title << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "Availability: " << (books[i].isAvailable ? "Available" : "Not Available") << endl;
        cout << "-----------------------" << endl;
    }
}

void borrowBook(Book* books, int bookCount, User* users, int userCount)
{
    if (bookCount == 0)
    {
        cout << "No books in the library." << endl;
        return;
    }
    if (userCount == 0)
    {
        cout << "No users in the system." << endl;
        return;
    }

    int userId, bookId;
    cout << "Enter your user ID: ";
    cin >> userId;
    cout << "Enter book ID to borrow: ";
    cin >> bookId;

    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == userId)
        {
            if (users[i].borrowedBookId != -1)
            {
                cout << "You have already borrowed a book. Please return it first." << endl;
                return;
            }
            for (int j = 0; j < bookCount; j++)
            {
                if (books[j].id == bookId)
                {
                    if (books[j].isAvailable)
                    {
                        books[j].isAvailable = false;
                        users[i].borrowedBookId = bookId;
                        cout << "You borrowed \"" << books[j].title << "\" by " << books[j].author << endl;
                    }
                    else
                    {
                        cout << "Book is not available." << endl;
                    }
                    return;
                }
            }
            cout << "Book with ID " << bookId << " not found." << endl;
            return;
        }
    }
    cout << "User with ID " << userId << " not found." << endl;
}

void returnBook(Book* books, int bookCount, User* users, int userCount)
{
    if (bookCount == 0)
    {
        cout << "No books in the library." << endl;
        return;
    }
    if (userCount == 0)
    {
        cout << "No users in the system." << endl;
        return;
    }

    int userId;
    cout << "Enter your user ID: ";
    cin >> userId;

    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == userId)
        {
            if (users[i].borrowedBookId == -1)
            {
                cout << "You have not borrowed any book." << endl;
                return;
            }
            for (int j = 0; j < bookCount; j++)
            {
                if (books[j].id == users[i].borrowedBookId)
                {
                    books[j].isAvailable = true;
                    cout << "You returned \"" << books[j].title << "\" by " << books[j].author << endl;
                    users[i].borrowedBookId = -1;
                    return;
                }
            }
        }
    }
    cout << "User with ID " << userId << " not found." << endl;
}

void searchBook(const Book* books, int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books in the library." << endl;
        return;
    }

    char keyword[TITLE_LENGTH];
    cout << "Enter title or author to search: ";
    cin.ignore();
    cin.getline(keyword, TITLE_LENGTH);

    bool found = false;
    for (int i = 0; i < bookCount; ++i) 
    {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) 
        {
            cout << "ID: " << books[i].id << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Availability: " << (books[i].isAvailable ? "Available" : "Not Available") << endl;
            cout << "-----------------------" << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No books found matching the keyword." << endl;
    }
}
void addUser(User* users, int* userCount)
{
    if (*userCount >= MAX_USERS)
    {
        cout << "User limit reached. Cannot add more users." << endl;
        return;
    }

    User* user = &users[*userCount];
    cout << "Enter user name: ";
    cin.ignore();
    cin.getline(user->name, NAME_LENGTH);
    user->id = *userCount + 1;
    user->borrowedBookId = -1;

    (*userCount)++;
    cout << "User added successfully!" << endl;
}

void displayUsers(const User* users, int userCount)
{
    if (userCount == 0)
    {
        cout << "No users in the system." << endl;
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        const User* user = &users[i];
        cout << "ID: " << user->id << endl;
        cout << "Name: " << user->name << endl;
        cout << "-----------------------" << endl;
    }
}