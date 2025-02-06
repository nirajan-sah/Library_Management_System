#include <iostream> 	
#include <string>	
#include <conio.h>
#include <iomanip>	
#include <fstream>	
#include <ctime>	
#include <string>
#include <sstream>

using namespace std;

class Membership
{
    private:
    int StudentNumber;       
    string StudentName;        

    public:
    // Default constructor
    Membership():StudentNumber(0), StudentName(""){}

    // Parameterized constructor
    Membership(int id, string name) : StudentNumber(id), StudentName(name){
        ofstream database;
        database.open("students.txt", ios::out | ios::app);
        database << StudentNumber <<" "<< StudentName << endl; // Write product details
        cout << "\n\n\n\tMEMBER CREATED SUCCESSFULLY";
        getch(); 
    }

    // Getter
    int getID() { return StudentNumber; }
    string getName() { return StudentName; }

    // Setter
    void setID(int x) { StudentNumber = x; }
    void setName(string x) { StudentName = x; }
};

class Book
{
    private:
    string Author;
    int BookId;
    string BookName;

    public:
    Book():BookId(0), BookName(""), Author(""){}

    Book(int code, string name, string writer):BookId(code), BookName(name), Author(writer)
    {
        ofstream bookbase;
        bookbase.open("library.txt", ios::out | ios::app);
        bookbase << BookId <<" "<< BookName <<" "<< Author <<endl;
        cout << " Book added to the list!! ";
        getch(); 
    }
    int getBookId(){return BookId;}
    string getBookName(){return BookName;}
    string getAuthor() { return Author;}

    void setBookId(int x){BookId = x;}
    void setBookName(string x){BookName = x;}
    void setAuthor(string x){Author = x;}
};

class Admin {
protected:
    static void addAdminUser() {
        string newUsername, newPassword, confirmPassword;

        cout << "\n\n\tEnter New Admin Username: "; 			
        cin >> newUsername;

        cout << "\n\n\tEnter New Admin Password: ";				
        char ch;
        while ((ch = getch()) != '\r') 							
		{ 
            if (ch == '\b' && !newPassword.empty()) {			
                newPassword.pop_back();							
                cout << "\b \b";								
            } else if (ch != '\b') {							
                newPassword += ch;								
                cout << '*';									
            }
        }

		//using same algorithm as before
        cout << "\n\n\tConfirm Password: ";			
        while ((ch = getch()) != '\r') {
            if (ch == '\b' && !confirmPassword.empty()) {
                confirmPassword.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                confirmPassword += ch;
                cout << '*';
            }
        }

		//confirm
        if (newPassword != confirmPassword) {
            cout << "\n\n\tError: Passwords do not match. Admin user not added.";
            cout << "\n\tPress any key to continue...";
            getch();
            return;
        }

		//store the password in the file admindatabase.txt
        ofstream adminData("admindatabase.txt", ios::app);
        if (!adminData) {
            cerr << "\n\n\tError: Unable to access admindatabase file.";	
            cout << "\n\tPress any key to continue...";
            getch();
            return;
        }

        adminData << newUsername << ' ' << newPassword << '\n';					
        adminData.close();

        cout << "\n\n\tNew Admin User Added Successfully!";
        cout << "\n\tPress any key to continue...";
        getch();
    }

	//static bool is entered because we only expect output of true or false from this.
    static bool authorizeAdmin() {
        const string defaultAdminUsername = "admin"; // Default admin username
        const string defaultAdminPassword = "1234"; // Default admin password

        string enteredUsername, enteredPassword;
        char ch;

        cout << "\n\n\tEnter Admin Username: ";
        cin >> enteredUsername;
        cout << "\n\tEnter Admin Password: ";
        enteredPassword = "";

        // Hide password input
        while ((ch = getch()) != '\r') { // Enter key ends input
            if (ch == '\b' && !enteredPassword.empty()) {
                enteredPassword.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                enteredPassword += ch;
                cout << '*';
            }
        }

        // Check default login first
        if (enteredUsername == defaultAdminUsername && enteredPassword == defaultAdminPassword) {
            cout << "\n\tDefault Admin Login Successful!";
            return true;
        }

        // Check stored login detail in admindatabase.txt
        ifstream adminFile("admindatabase.txt");
        string fileUsername, filePassword;
        while (adminFile >> fileUsername >> filePassword) {
            if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                cout << "\n\tAdmin Login Successful!";
                adminFile.close();
                return true;
            }
        }

        adminFile.close();
        cout << "\n\tLogin Failed! Invalid Username or Password.";
        return false;
    }
};

class td
{
    public:
    string date;
    td()
    {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        ostringstream oss;
        oss<<setfill('0')<<setw(2)<<localTime->tm_mday<<"/"
            <<setfill('0')<<setw(2)<<(localTime->tm_mon + 1);
        date = oss.str();
    }

};

class BookItems
{
    private:
    Book book;

    public:
    void getBook()
    {
        ifstream borrow;
        int code;
        bool found = false;
            cout<<"\n\tEnter the Book Id: ";
            cin>>code;
            borrow.open("library.txt", ios::in);

            if(!borrow)
            {
                cout<<"\n\tError: Unable to open products file!";
                return;
            }

            int bi;
            string bn;
            string ba;

            while(borrow >> bi >> bn >>ba )
            {
                if(bi == code)
                {
                    book.setBookId(bi);
                    book.setBookName(bn);
                    book.setAuthor(ba);
                }
            }
            borrow.close();
            getch();
    }   
    void printdetails()
    {
        cout
            <<"\t"<<setw(7)<<book.getBookId()
            <<"\t"<<setw(15)<<book.getBookName()
            <<"\t"<<setw(16)<<book.getAuthor()<<"\t"<<endl;
    }
    int getID(){return book.getBookId();}
    string getName(){return book.getBookName();}
    string getBookAuthor(){return book.getAuthor();}

};

class Borrow : public td
{
    public:
    int numofBooks;
    string studentid;
    BookItems book[50];

    void storeHistory()
    {
        ofstream history;
        history.open("history.txt", ios::out | ios::app);
        history<<"\n\tStudent ID\tBorrow Date\tBook Id\t\tBook Name\tBook Author\t"<<endl;
        history<<"\t"<<setw(10)<<studentid
                <<"\t"<<setw(10)<<date;

        for(int i = 0; i < numofBooks; i++)
        {
            history <<"\t"<<setw(7) << book[i].getID()
                    <<"\t"<<setw(15)<<book[i].getName()
                    <<"\t"<<setw(16)<<book[i].getBookAuthor()<<endl;

        }
        history.close();
    }
};

class auth
{
    protected:
    static bool authstudent(string enteredUsername, string ID) {
        const string defaultUsername = "student"; // Default admin username
        const string defaultPassword = "1221"; // Default admin password

       

        // Check default login first
        if (enteredUsername == defaultUsername && ID == defaultPassword) {
            cout << "\n\tDefault student Login Successful!";
            return true;
        }

        // Check stored login detail in admindatabase.txt
        ifstream studentfile("students.txt");
        string fileUsername, filePassword;
        while (studentfile >> filePassword >> fileUsername) {
            if (fileUsername == enteredUsername && filePassword == ID) 
            {
                cout << "\n\tAdmin Login Successful!";
                studentfile.close();
                return true;
            }
        }

        studentfile.close();
        cout << "\n\tLogin Failed! Invalid Username or Password.";
        return false;
    }
};

class Navpages : public Admin, public auth
{
    public:
    static void UserMenu()
    {
        int ch;
        system("cls");
        cout<<"\n\n\t\t\tWelcome to E-Library"<<endl;
        cout<<"\n\t\t\t===================="<<endl;
        cout<<"\n\t1. STUDENT";
        cout<<"\n\t2. ADMINISTRATOR";
        cout<<"\n\t3. EXIT";
        cout<<"\n\n\n\t Please select your option(1 - 3): ";
        do{cin>>ch;}while(ch < 0 || ch > 3);
        switch(ch)
        {
            case 1: student(); break;
            case 2: admin(); break;
            case 3: exit(0);
        }
    }
    
    static void student()
    {
        int n, c;
        string name;
        BookItems book[20];
        int code;
        Borrow fBill;
        system("cls");
        cout<<"\n\n\t1. Back to Main Menu";
        cout<<"\n\n\t2. Continue";
        cout<<"\n\n\tChoose: ";
        cin>>c;
        switch(c)
        {
            case 1: return;
            case 2: break;
            default: cout<<"\nInvalid option\n"; return;
        }
        string enteredUsername, enteredPassword;
        string ID;

        cout << "\n\n\tEnter Student Name: ";
        cin >> enteredUsername;
        cout << "\n\tEnter Student ID: ";
        cin >> ID;

        if(!authstudent(enteredUsername, ID))
        {
            cout<<"\n\n\t Returning to main menu \n";
            getch();
            return;
        }

        system("cls");

        while(true)
        {
            cout << "\n\n\tEnter the number of books to borrow: ";
            cin >> n;
            system("cls");
            displayBook();

            fBill.numofBooks = n;
            fBill.studentid = ID;

            for(int i = 0; i < n; i++)
            {
                cout<<"\n\tAdding Book "<<(i + 1)<<": ";
                book[i].getBook();

                while(false)
                {
                    return;
                }
                fBill.book[i] = book[i];
            }

            system("cls");

            cout <<"\n\tStudent ID\tBorrow Date\tBook Id\t\tBook Name\tBook Author"<<endl;
            cout<<"\t"<<setw(10)<<fBill.studentid
                <<"\t"<<setw(10)<<fBill.date;

            for(int i = 0; i < n; i++)
            {
                book[i].printdetails(); 

            }
            break;
        }
        cout<<"\n\n\tBook borrowed successfully..";
        getch();
        fBill.storeHistory();
    }

    static void admin()
    {
        if(!authorizeAdmin())
        {
            cout<<"\n\n\tReturning to the main menu.";
            getch();
            return;
        }
        while(true)
        {
            system("cls");
            int ch;
            cout<<"\n\n\tAdmin Portal";
            cout<<"\n\n\t1. Create a Book";
            cout<<"\n\n\t2. Display all Book";
            cout<<"\n\n\t3. Delete Book";
            cout<<"\n\n\t4. Display all history";
            cout<<"\n\n\t5. Register a Student";
            cout<<"\n\n\t6. Register a Admin";
            cout<<"\n\n\t7. Back to main menu";
            cout<<"\n\n\n\n\tPlease Enter Your choice: ";
            cin>>ch;
            switch(ch)
            {
                case 1: createBook(); break;
                case 2: displayBook(); break;
                case 3: DeleteBook(); break;
                case 4: DisplayHistory(); break;
                case 5: RegisterStudent(); break;
                case 6: RegisterAdmin(); break;
                case 7: return;
                default: cout<<"error";
            }
        }
    }

    static void displayBook()
    {
        system("cls");
        ifstream displayBooks;
        displayBooks.open("library.txt",ios::in);
        int n;
        string name;
        string author;
        cout<<"\n\n\tDisplaying all the books"<<"\n\t=======================================================\n";
        while(true)
        {
            displayBooks >> n;
            if(displayBooks.eof())
            {break;}
            displayBooks >> name >> author;
            cout << "\n\tBook Code: "<<n;
            cout << "\n\tBook Name: "<<name;
            cout << "\n\tBook author: "<<author;
            cout << "\n\t=========================================";
        }
        cout<<"\n\tPress any key to continue";
        getch();
    }

    static bool isuniqueNumber(int number)
    {
        ifstream inbooks("library.txt", ios::in);
        if(inbooks.is_open())
        {
            string line;
            while(getline(inbooks, line))
            {
                stringstream ss(line);
                int num;
                ss >>num;
                if(num == number)
                {
                    inbooks.close();
                    return false;
                }
            }
            inbooks.close();
        }
        return true;
    }

    static void createBook()
    {
        system("cls");
        int n;
        string p, r;
        cout << "\n\n\tEnter the Detail of Books" << endl;
        cout << "\n\tEnter the Book number: ";
        cin >> n;
        while(!isuniqueNumber(n))
        {
            cout<<"\n\tThe number already exist.\n\tPlease enter a unique number\n";
            cin>>n;
        }
        cout << "\n\tEnter the name of the book: ";
        cin >> p;
        cout << "\n\tEnter the author of the book: ";
        cin >> r;
        Book book(n, p, r);
    }

    static void DeleteBook()
    {
        int n;
        string name, author;

        system("cls");
        displayBook();
        ifstream bookin;
        ofstream booktmp;
        cout<<"\n\t*****************************************************************";
        cout<<"\n\tEnter the Book Number to delete: ";
        int modnum;
        cin >> modnum;
        bookin.open("library.txt", ios::in);
        booktmp.open("temp.txt", ios::out);

        while(1)
        {
            bookin >> n;
            if (bookin.eof())
            {
                break;
            }

            bookin >> name >> author;

            if(n != modnum)
            {
                booktmp << n <<" "<< name<<" " << author <<endl;
            }

            bookin.close();
            booktmp.close();
            remove("library.txt");
            rename("temp.txt", "library.txt");
            cout<<"\n\n\tThe book is deleted successfully!";
            getch();

        }
    }

    static void DisplayHistory()
    {
        system("cls");
        ifstream history;
        history.open("history.txt", ios::in);
        if(!history)
        {
            cout<<"\n\n\tNo history is found!";
            cout<<"\n\n\tPress any key";
            getch();
            return;
        }

        string line;
        cout<<"\n\n\tDisplaying all History"<<"\n\t==============================================================================\n";
        while(getline(history, line))
        {
            cout << line << endl;
        }
        history.close();
        cout<<"\n\n\tPress any key";
        getch();
    }

    static void RegisterStudent()
    {
        int n;
        string name;

        cout<<"\n\tEnter the student name: ";
        cin>>name;

        cout<<"\n\tEnter the student ID: ";
        cin>>n;

        Membership student(n, name);
    }

    static void RegisterAdmin()
    {
        addAdminUser();
    }
    
};

int main()
{
    system("cls");
    while (1)
    {
        Navpages::UserMenu();
    }
    
    return 0;
}
