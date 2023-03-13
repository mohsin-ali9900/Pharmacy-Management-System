#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <sstream>
using namespace std;

void topheader();
void loginmenu();
void signup(string, string, string);
string login(string, string);
void admin();
void customer();

void deletestock();
void addstock();
void showstock();
void updatestock(string, int);
void updateprices();
void savedata(string, int);
void manageworkers();
void updatenamepassadmin();
void offerdicount();

void writeMedicine();
string getField(string record, int field);
void readMedicine();
void writeSignUp();
void readSignUp();

int checkbill(string, int);
void updatenamepasscustomer();
void checkprice();
int payment(int);
int discountprice(int);
int changeprice(int, string);

const int arraysize = 100;
string name[arraysize];
string password[arraysize];
string role[arraysize];
int count = 0, countbill = 0;

string medicinename[50] = {"Panadol", "Calpol", "Dispirin", "Pioden", "Antibiotic"};
int mainmedicineCount = 5;
int prices[50] = {50, 40, 70, 90, 74};
int quantity[50] = {10, 20, 15, 26, 17};
string allusernames[50];
int allbills[50];
string alluserpasswords[50];

main()
{
    readMedicine();
    readSignUp();
    // credentials

    system("cls");
    string username, userpassword, userrole;
    int choice;

    int loginoption = 0;
    while (loginoption != 3)
    {
        system("cls");
        loginmenu();

        cout << "Enter the choice : ";
        cin >> choice;

        if (choice == 2)
        {
            system("cls");
            topheader();
            cout << "        SIGN UP >        " << endl;
            cout << "*************************" << endl;
            cout << "Enter the username : ";
            cin >> username;
            cout << "Enter the password : ";
            cin >> userpassword;
            cout << "Enter the role : ";
            cin >> userrole;

             if ((username.length() > 2) && (userpassword.length() > 2) && (userrole == "admin" || userrole == "customer"))
            {
                signup(username, userpassword, userrole);
                writeSignUp();
            }
            else
            {
                cout << "Invalid username,password or role";
                getch();
            }
        }
        else if (choice == 1)
        {
            system("cls");
            topheader();
            cout << "         LOGIN >         " << endl;
            cout << "*************************" << endl;
            cout << "Enter the username : ";
            cin >> username;
            cout << "Enter the password : ";
            cin >> userpassword;
            string output = login(username, userpassword);
            if (output == "admin")
            {
                int choice;
                while (choice != 0)
                {
                    admin();
                    cout << "Enter the option : ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        system("cls");
                        topheader();
                        cout << "        ADD STOCK >        " << endl;
                        cout << "*************************" << endl;
                        addstock();
                        writeMedicine();
                    }
                    else if (choice == 2)
                    {
                        system("cls");
                        topheader();
                        cout << "      DELETE STOCK >        " << endl;
                        cout << "*************************" << endl;
                        deletestock();
                        writeMedicine();
                    }
                    else if (choice == 3)
                    {
                        system("cls");
                        topheader();
                        cout << "      UPDATE STOCK >     " << endl;
                        cout << "*************************" << endl;
                        updateprices();
                        writeMedicine();
                    }
                    else if (choice == 4)
                    {
                        showstock();
                    }
                    else if (choice == 5)
                    {
                        manageworkers();
                    }
                    else if (choice == 6)
                    {
                        offerdicount();
                    }
                    else if (choice == 7)
                    {
                        //           In this admin can see the username and their bill prices to keep track of data.
                        topheader();
                        cout << "      SAVE DATA >        " << endl;
                        cout << "*************************" << endl;
                        cout << "Username"
                             << "\t\t\t"
                             << "bill" << endl;
                        for (int i = 0; i < countbill; i++)
                        {
                            savedata(allusernames[i], allbills[i]);
                        }
                        cout<<"Enter any key to Exit."<<endl;
                        getch();
                    }
                    else if (choice == 8)
                    {
                        updatenamepassadmin();
                    }
                    else if (choice == 9 || choice < 1 || choice > 9)
                    {
                        break;
                    }
                }
            }
            else if (output == "customer")
            {

                //                          In this we calculate and prints bill.
                int choice1=-1;
                while (choice1 != 0)
                {
                    system("cls");
                    topheader();
                    customer();
                    cout << "Enter the choice : ";
                    cin >> choice1;
                    int totalbill;
                    int change = 0;

                    if (choice1 == 1)
                    {
                        system("cls");
                        topheader();
                        cout << "       CHECK BILL >      " << endl;
                        cout << "*************************" << endl;
                        int noofmedrequired;
                        int total = 0;
                        int dicountedprice;
                        bool istrue = false;
                        cout << "Enter no of medicines required : ";
                        cin >> noofmedrequired;
                        int quantitypermedicine[noofmedrequired];
                        string billmedicinename[noofmedrequired];
                        for (int i = 0; i < noofmedrequired; i++)
                        {
                            cout << "Enter name of medicine : ";
                            cin >> billmedicinename[i];
                            cout << "Enter quantity of ach medicine : ";
                            cin >> quantitypermedicine[i];

                            for (int j = 0; j < mainmedicineCount; j++)
                            {
                                if (billmedicinename[i] == medicinename[j])
                                {
                                    istrue = true;
                                }
                            }
                            if (istrue == true)
                            {
                                updatestock(billmedicinename[i], quantitypermedicine[i]); // decrese the quantity in stock accordingly.

                                totalbill = checkbill(billmedicinename[i], quantitypermedicine[i]);
                                total = total + totalbill;
                            }
                            else
                            {
                                cout << "Required medicine is not in the stock." << endl;
                                getch();
                            }
                        }
                        if (istrue == true)
                        {
                            if (total > 300) // discount is offered on bill grester than 300
                            {
                                dicountedprice = discountprice(total);
                                cout << "Discounted price is :" << dicountedprice;
                                total = total - dicountedprice;
                            }

                            allbills[countbill] = total;
                            allusernames[countbill] = username;
                            alluserpasswords[countbill] = userpassword;

                            // Printing Bill.
                            system("cls");
                            cout << "Medicine"
                                 << "\t\t\t"
                                 << "Quantity" << endl;
                            for (int j = 0; j < noofmedrequired; j++)
                            {
                                cout << billmedicinename[j] << "\t\t\t\t\t" << quantitypermedicine[j] << endl;
                            }

                            cout << "Total Bill is : " << total << endl;
                            change = payment(total);
                            countbill++;

                            cout << "Thanks. Bill payed successfully. " << endl;
                            cout << "your change is : " << change << endl;
                            getch();

                            cout << "Toatal bill is :" << total;
                        }
                    }
                    else if (choice1 == 2)
                    {
                        topheader();
                        cout << "    UPDATE NAME AND PASSWORD >             " << endl;
                        cout << "**********************************" << endl;
                        updatenamepasscustomer();
                    }
                    else if (choice1 == 3)
                    {
                        checkprice();
                        getch();
                    }
                    else if (choice1 == 4 || choice1 > 4 || choice1 < 1)
                    {
                        break;
                    }
                }
            }
        }
        else
        {

            // cout << "Invalid username/password";
            // getch();
            break;
        }
    }
}

//  Main Header
void topheader()
{
    cout << "#######################################################################################################" << endl;
    cout << "#######################################################################################################" << endl;
    cout << "#####                                                                                             #####" << endl;
    cout << "#####                               PHARMACY  MANAGEMENT  SYSTEM                                  #####" << endl;
    cout << "#####                                                                                             #####" << endl;
    cout << "#######################################################################################################" << endl;
    cout << "#######################################################################################################" << endl;
}

// Login Menu
void loginmenu()
{
    topheader();
    cout << "    LOGIN MENU >             " << endl;
    cout << "*************************" << endl;
    cout << "1.  SignIn with your credentials. " << endl;
    cout << "2.  SignUp to get your credentials. " << endl;
    cout << "3.  Exit program. " << endl;
    cout << "    " << endl;
}

// Signup Funtion
void signup(string name2, string password2, string role2)
{
    // Checking if the account already exists.
    // If it exists it will terminate the progrm.
    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            if (name2 == name[i] && role2 == role[i])
            {
                cout << "This account already exists." << endl;
                count = count;
            }
            else
            {
                name[count] = name2;
                password[count] = password2;
                role[count] = role2;

                count++;
            }
        }
    }
    else
    {
        name[count] = name2;
        password[count] = password2;
        role[count] = role2;

        count++;
    }
}

//   Login Function
string login(string name1, string password1)
{
    string roles;
    for (int i = 0; i < count; i++)
    {
        if ((name1 == name[i]) && (password1 == password[i]))
        {
            roles = role[i];
        }
    }

    return roles;
}

// Admin menu
void admin()
{
    system("cls");
    topheader();
    cout << "    ADMIN MENU >             " << endl;
    cout << "*************************" << endl;
    cout << "1.  Add Stock. " << endl;
    cout << "2.  Delete Bills. " << endl;
    cout << "3.  Update Prices. " << endl;
    cout << "4.  Show stock. " << endl;
    cout << "5.  Manage Workers. " << endl;
    cout << "6.  Offer Discount. " << endl;
    cout << "7.  Save Data. " << endl;
    cout << "8.  Update username/password   " << endl;
    cout << "9.  Press 9 to exit." << endl;
}

//  Customer Menu
void customer()
{
    system("cls");
    topheader();
    cout << "    CUSTOMER MENU >             " << endl;
    cout << "*************************" << endl;
    cout << "1.  Check Bill. " << endl;
    cout << "2.  Update name and password. " << endl;
    cout << "3.  Check prices. " << endl;
    cout << "4.  Exit. " << endl;
    cout << "    " << endl;
}

// ##############################
// ###  functions of Admin    ###
// ##############################

//   Delete Stock Function
void deletestock()
{
    string deletemedicine;
    cout << "Enter product you want to delete : ";
    cin >> deletemedicine;

    for (int i = 0; i < mainmedicineCount; i++)
    {
        if (deletemedicine == medicinename[i])
        {
            for (int z = i; z < mainmedicineCount; z++)
            {
                medicinename[z] = medicinename[z + 1];
                prices[z] = prices[z + 1];
                quantity[z] = quantity[z + 1];
            }
            mainmedicineCount--;
        }
    }
}

//   Add Stock Function
void addstock()
{
    string addnewmedicine;
    int newmedicineprice, newmedicinequantity;

    cout << "Enter name of medicine to added : ";
    cin >> addnewmedicine;
    cout << "Enter price of new medicine : ";
    cin >> newmedicineprice;
    cout << "Enter quantity of new medicine : ";
    cin >> newmedicinequantity;

    medicinename[mainmedicineCount] = addnewmedicine;
    prices[mainmedicineCount] = newmedicineprice;
    quantity[mainmedicineCount] = newmedicinequantity;
    mainmedicineCount++;
    cout << "count    " << mainmedicineCount;
}

//   Update Price Function
void updateprices()
{
    string medicinetobeupdated;
    int updatedprice;
    cout << "Enter name of medicine to be updated : ";
    cin >> medicinetobeupdated;
    cout << "Enter the new price : ";
    cin >> updatedprice;

    //  if we add invalid medicine name it will show that it is invalid.
    for (int i = 0; i < mainmedicineCount; i++)
    {
        if (medicinename[i] == medicinetobeupdated)
        {
            prices[i] = updatedprice;
            break;
        }
        else
        {
            cout << "Invalid medicine name ." << endl;
            getch();
            break;
        }
    }
}

//   Update Stock Function
void updatestock(string soldmedicinename, int soldmedicinequantity)
{
    for (int i = 0; i < mainmedicineCount; i++)
    {
        if (soldmedicinename == medicinename[i])
        {
            quantity[i] = quantity[i] - soldmedicinequantity;
        }
    }
}

//   Show / Display Stock Function
void showstock()
{
    system("cls");
    topheader();
    cout << "    PRICE CHECK MENU >             " << endl;
    cout << "*************************" << endl;
    cout << "  Medicine"
         << "\t\t\t"
         << "Price"
         << "\t\t\t"
         << "quantity" << endl;
    for (int i = 0; i < 50; i++)
    {
        if (medicinename[i] == "")
        {
            break;
        }
        cout << i + 1 << ".  " << medicinename[i] << "\t\t\t" << prices[i] << "\t\t\t" << quantity[i] << endl;
    }
    cout << "    Press any key to exit.    " << endl;
    getch();
}

//   Function for saving bills
void savedata(string billsusername, int billamount)
{
    cout << billsusername << "\t\t\t" << billamount << endl;

    getch();
}

//   in this function admin tell the required amount of workers and their salary.
void manageworkers()
{
    system("cls");
    topheader();
    cout << "    WORKERS REQUIREMENT >             " << endl;
    cout << "*************************" << endl;
    int noofworkers, salary;
    cout << "Enter no of workers required : ";
    cin >> noofworkers;
    cout << "Enter salary of each worker : ";
    cin >> salary;
    getch();
}

// Fuction to Update name and password of admin
void updatenamepassadmin()
{
    string usernametobeupdated, passwordtobeupdated, newupdatedusername, newupdatedpassword;
    cout << "Enter old username to be updated : ";
    cin >> usernametobeupdated;
    cout << "Enter the old password to be updated : ";
    cin >> passwordtobeupdated;
    cout << "Enter new username to be updated : ";
    cin >> newupdatedusername;
    cout << "Enter new old password to be updated : ";
    cin >> newupdatedpassword;
    for (int i = 0; i <= 50; i++)
    {
        if (usernametobeupdated == name[i] && passwordtobeupdated == password[i])
        {
            name[i] = newupdatedusername;
            password[i] = newupdatedpassword;
            break;
        }
    }
}

//   In this fuction admin offer discount based on condition.
void offerdicount()
{
    system("cls");
    topheader();
    cout << "    DISCOUNT CONDITION >             " << endl;
    cout << "*************************" << endl;
    cout << "If total bill is greater than 300 than offer 15% discount.";
    getch();
}

// ##############################
// ###  functions of customer ###
// ##############################

// Fuction to generate bill
int checkbill(string billmedicinename, int quantitypermedicine)
{
    int totalbill = 0;
    cout << mainmedicineCount;
    for (int i = 0; i < mainmedicineCount; i++)
    {
        if (billmedicinename == medicinename[i])
        {
            totalbill = totalbill + prices[i] * quantitypermedicine;
        }
    }
    return totalbill;
}

// Fuction to Update name and password of user
void updatenamepasscustomer()
{
    string usernametobeupdated, passwordtobeupdated, newupdatedusername, newupdatedpassword;
    cout << "Enter old username to be updated : ";
    cin >> usernametobeupdated;
    cout << "Enter the old password to be updated : ";
    cin >> passwordtobeupdated;
    cout << "Enter new username to be updated : ";
    cin >> newupdatedusername;
    cout << "Enter new old password to be updated : ";
    cin >> newupdatedpassword;
    getch();

    for (int i = 0; i < 50; i++)
    {
        if (usernametobeupdated == name[i] && passwordtobeupdated == password[i])
        {
            name[i] = newupdatedusername;
            password[i] = newupdatedpassword;
            getch();
            break;
        }
    }
}

// Fuction to check medicines and their prices.
void checkprice()
{
    system("cls");
    topheader();
    cout << "    PRICE CHECK MENU >             " << endl;
    cout << "*************************" << endl;
    cout << "  Medicine"
         << "\t\t\t"
         << "Price" << endl;
    for (int i = 0; i < mainmedicineCount; i++)
    {
        for (int j = 0; j < mainmedicineCount; j++)
        {
            cout << i + 1 << ".  " << medicinename[i] << "\t\t\t" << prices[i] << endl;
        }
    }
    cout << "    Press any key to exit.    " << endl;
}

// In this funtion customer is asked for payment method and function return the remaining amount of customer.
int payment(int totalbillprice)
{
    string method;
    int change = 0;
    cout << "Payment method (cash/card) : ";
    cin >> method;
    change = changeprice(totalbillprice, method);
    return change;
}

// In this function discount is calculated.
int discountprice(int totalprice)
{
    int discountedprice;
    discountedprice = (totalprice * 15) / 100;
    return discountedprice;
}

// In this function the remaing amount that is to be given back to customer is calculated.
int changeprice(int totalbillprice, string method)
{
    int cutomeramount, change = 0, pin;
    if (method == "cash")
    {
        cout << "Your amount : ";
        cin >> cutomeramount;
        change = cutomeramount - totalbillprice;
    }
    else if (method == "card")
    {
        cout << "Enter the pin : ";
        cin >> pin;
        cout << "Enter the amount in card : ";
        cin >> cutomeramount;
        change = cutomeramount - totalbillprice;
    }
    return change;
}
//-------------------------------------------------FILE HANDLING ------------------------------------------------

void writeMedicine()
{
    fstream med;
    med.open("medicine.txt", ios::out);
    for (int i = 0; i < 50; i++)
    {
        if (medicinename[i] == "")
        {
            break;
        }
        med << medicinename[i] << "," << prices[i] << "," << quantity[i] << endl;
    }
    med.close();
}
string getField(string record, int field)
{
    int commaCount = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}
void readMedicine()
{
    int x = 0;
    fstream med;
    string word;
    string price, quantitys;
    med.open("medicine.txt", ios::in);
    while (!med.eof())
    {
        getline(med, word);
        if (word == "")
        {
            mainmedicineCount = x;
            break;
        }
        medicinename[x] = getField(word, 1);
        price = getField(word, 2);
        quantitys = getField(word, 3);
        istringstream(price) >> prices[x];
        istringstream(quantitys) >> quantity[x];
        x++;
    }
    med.close();
}


void writeSignUp()
{
    fstream sign;
    sign.open("signUp.txt", ios::out);
    for (int i = 0; i < arraysize; i++)
    {
        if (name[i] == "")
        {
            continue;
        }
        sign << name[i] << "," << password[i] << "," << role[i] << endl;
    }
    sign.close();
}

void readSignUp()
{
    int count1=0;
    fstream sign;
    string word;
    sign.open("signUp.txt", ios::in);
    while (!sign.eof())
    {
        getline(sign, word);
         if (word == "")
         {
            count=count1;
             break;
         }

        name[count1] =  getField(word, 1);
        password[count1] = getField(word, 2);
        role[count1] = getField(word, 3);
        count1++;
    }
    sign.close();
}