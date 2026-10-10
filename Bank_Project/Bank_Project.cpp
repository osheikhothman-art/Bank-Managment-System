#pragma warning (disable : 4996)
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>

using namespace std;

enum enMenu { ClientList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8 };
enum enTransactionsMenu {Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4};
enum enManageUsers {UsersList = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenue = 6};

struct stClientData {
	string AccountNumber;
	string Name;
	string PinCode;
	string Phone;
	double AccountBalance;
	bool MarkForDeletion = false;
};

struct stUsers {
	string UserName;
	string PassWord;
	int Permissions;
	bool MarkForDeletion = false;
};

void Start(vector <stClientData>& vClientData, vector <stUsers>& vUsersData, stUsers UserData);
void Login();

vector <string> Splite(string Text, string Delim = "#//#")
{
	vector <string> vString;
	int pos = 0;
	string word;

	while ((pos = Text.find(Delim)) != std::string::npos)
	{
		word = Text.substr(0, pos);
		if (word != "")
		{
			vString.push_back(word);
		}
		Text.erase(0, pos + Delim.length());
	}
	if (Text != "")
	{
		vString.push_back(Text);
	}
	return vString;
}
string ConvertRecordToLine(stClientData ClientData, string Seperator = "#//#")
{
	string sClientData = "";

	sClientData += ClientData.AccountNumber + Seperator;
	sClientData += ClientData.Name + Seperator;
	sClientData += ClientData.PinCode + Seperator;
	sClientData += ClientData.Phone + Seperator;
	sClientData += to_string(ClientData.AccountBalance);

	return sClientData;
}
vector <stClientData> LoadClientDataFromFile(string FilePath)
{
	vector <stClientData> vstClientData;
	vector <string> sClientData;
	stClientData ClientData;
	fstream MyFile;
	string line = "";
	MyFile.open(FilePath, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			sClientData = Splite(line);
			if (sClientData.size() == 5)
			{
				ClientData.AccountNumber = sClientData[0];
				ClientData.Name = sClientData[1];
				ClientData.PinCode = sClientData[2];
				ClientData.Phone = sClientData[3];
				ClientData.AccountBalance = stod(sClientData[4]);
				vstClientData.push_back(ClientData);
			}
		}
		MyFile.close();
	}
	return vstClientData;
}
bool FindClientByAccountNumber(string AccountNumber, vector <stClientData> vClinetData, stClientData& ClientData)
{
	for (stClientData C : vClinetData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			ClientData = C;
			return true;
		}
	}
	return false;
}
void TheDesign()
{
	cout << "================================================================================" << endl;
	cout << "                                       Main Menu Screen                         " << endl;
	cout << "================================================================================" << endl;
	cout << "[1] Show Client List." << endl;
	cout << "[2] Add New Client." << endl;
	cout << "[3] Delete Client." << endl;
	cout << "[4] Update Client Info." << endl;
	cout << "[5] Find Client." << endl;
	cout << "[6] Transactions." << endl;
	cout << "[7] Manage Users." << endl;
	cout << "[8] Logout." << endl;
	cout << "================================================================================" << endl;
}

void ClientDataList1(vector <stClientData> vClientData)
{
	cout << "                                      Client List ( " << vClientData.size() << " ) Client(S)." << endl;
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << setw(25) << "| Account Number      | Client Name         | Pin Code            | Phone               | Balance    " << endl;
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
}
void ClientDataList2(vector <stClientData> vClientData)
{
	fstream MyFile;
	vector <string> vString;
	MyFile.open("D:\\Coding\\C++\\ClientData.txt", ios::in);
	if (MyFile.is_open())
	{
		string stLine = "";
		while (getline(MyFile, stLine))
		{
			vString = Splite(stLine);
			cout << "| " << left << setw(20) << vString[0] << "| " << setw(20) << vString[1] << "| " << setw(20) << vString[2] << "| " << setw(20) << vString[3] << "| " << setw(20) << vString[4] << endl;
		}
		cout << endl;
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;
		MyFile.close();
	}
}

stClientData ReadClientInfo(string AccountNumber)
{
	stClientData ClientData;

	ClientData.AccountNumber = AccountNumber;
	cout << "Enter Your Pin Code: ";
	getline(cin >> ws, ClientData.PinCode);
	cout << "Enter Your Name: ";
	getline(cin >> ws, ClientData.Name);
	cout << "Enter Your Phone Number: ";
	getline(cin >> ws, ClientData.Phone);
	cout << "Enter Your Account Balance: ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}

bool AddNewClient(vector <stClientData>& vClientData)
{
	cout << "===============================================" << endl;
	cout << "                 Add New Client                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	stClientData Client;
	string AccountNumber = "";
	cout << "Enter Your Account Number: " << endl;
	getline(cin >> ws, AccountNumber);
	if (FindClientByAccountNumber(AccountNumber, vClientData, Client))
	{
		cout << "Sorry This Account Number ( " << Client.AccountNumber << " ) is Already Exist" << endl;
		return false;
	}
	stClientData ClientData = ReadClientInfo(AccountNumber);
	fstream MyFile;
	MyFile.open("D:\\Coding\\C++\\ClientData.txt", ios::app);
	if (MyFile.is_open())
	{
		string line = ConvertRecordToLine(ClientData);
		MyFile << line << endl;
	}
	MyFile.close();
	vClientData = LoadClientDataFromFile("D:\\Coding\\C++\\ClientData.txt");
	cout << endl;
	cout << "Your Data Has Add Successfully" << endl;
	cout << endl;
	return true;
}
void PrintRecord(stClientData ClientData)
{
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Account Name: " << ClientData.AccountNumber << endl;
	cout << "Pin Code: " << ClientData.PinCode << endl;
	cout << "Name: " << ClientData.Name << endl;
	cout << "Phone: " << ClientData.Phone << endl;
	cout << "Account Balance: " << ClientData.AccountBalance << endl;
	cout << "-------------------------------------------------------------" << endl;

}
void MarkClientAsDelete(string AccountNumber, vector <stClientData>& vClientData)
{
	for (stClientData& C : vClientData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDeletion = true;
		}
	}
}

void DeleteClient1(vector <stClientData>& vClientData)
{
	string stLine = "";
	fstream MyFile;
	MyFile.open("D:\\Coding\\C++\\ClientData.txt", ios::out);
	if (MyFile.is_open())
	{
		for (stClientData& C : vClientData)
		{
			if (C.MarkForDeletion == false)
			{
				stLine = ConvertRecordToLine(C);
				MyFile << stLine << endl;
			}
		}
	}
}

bool DeleteClientByAccountNumber(vector <stClientData>& vClientData)
{
	stClientData Client;
	char YesNo = ' ';
	string AccountNumber = "";
	cout << "===============================================" << endl;
	cout << "                 Delete Client                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << "Please Enter Your Account Number : " << endl;
	getline(cin >> ws, AccountNumber);
	if (FindClientByAccountNumber(AccountNumber, vClientData, Client))
	{
		cout << "Account Info : " << endl;
		cout << endl;
		PrintRecord(Client);

		cout << "Are You Sure You Want To Delete Your Account ? (Y/N)" << endl;
		cin >> YesNo;

		if (YesNo == 'y' || YesNo == 'Y')
		{
			MarkClientAsDelete(AccountNumber, vClientData);
			DeleteClient1(vClientData);

			vClientData = LoadClientDataFromFile("D:\\Coding\\C++\\ClientData.txt");
			cout << endl;
			cout << "Your Account With Name " << AccountNumber <<" Has Deleted Successfully" << endl;
			return true;
		}
	}
	else
	{
		cout << "Sorry This Account Number ( " << AccountNumber << " ) is Not Exist" << endl;
		return false;
	}
}

stClientData ChangeClientRecorde(string AccountNumber)
{
	stClientData Client;

	Client.AccountNumber = AccountNumber;
	cout << "Enter Your Pin Code: ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Your Name: ";
	getline(cin >> ws, Client.Name);
	cout << "Enter Your Phone Number: ";
	getline(cin >> ws, Client.Phone);
	cout << "Enter Your Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}
void SaveClientDataToFile(vector <stClientData> &vClientData)
{
	fstream MyFile;
	MyFile.open("D:\\Coding\\C++\\ClientData.txt", ios::out);
	if (MyFile.is_open())
	{
		for (stClientData& C : vClientData)
		{
			string Line = ConvertRecordToLine(C);
			MyFile << Line << endl;
		}
		MyFile.close();
	}
}
bool UpdateClientInfo(vector <stClientData> &vClientData)
{
	stClientData Client;
	char YesNo = ' ';
	string AccountNumber = "";
	cout << "===============================================" << endl;
	cout << "                 Update Client                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << "Please Enter Your Account Number : " << endl;
	getline(cin >> ws, AccountNumber);
	if (FindClientByAccountNumber(AccountNumber, vClientData, Client))
	{
		PrintRecord(Client);

		cout << "Are You Sure You Want To Update Your Account ? (Y/N) " << endl;
		cin >> YesNo;
		if (YesNo == 'Y' || YesNo == 'y')
		{
			for (stClientData& C : vClientData)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecorde(AccountNumber);
					break;
				}
			}
			SaveClientDataToFile(vClientData);
			vClientData = LoadClientDataFromFile("D:\\Coding\\C++\\ClientData.txt");
			cout << endl;
			cout << "Your Info Has Updated Successfully" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool FindClientFunction(vector <stClientData> vClientData)
{
	stClientData Client;
	string AccountNumber = "";
	cout << "===============================================" << endl;
	cout << "                 Find Client                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << "Please Enter Your Account Number : " << endl;
	getline(cin >> ws, AccountNumber);
	if (FindClientByAccountNumber(AccountNumber, vClientData, Client))
	{
		PrintRecord(Client);
		return true;
	}
	else
	{
		cout << "Sorry This Account Number ( " << AccountNumber << " ) is Not Found" << endl;
		return false;
	}
}
void TransactionsMenuScreen()
{
	cout << "====================================================" << endl;
	cout << "                 Transactions Menu                    " << endl;
	cout << "====================================================" << endl;
	cout << "\t" << "[1]Deposit." << endl;
	cout << "\t" << "[2]Withdraw." << endl;
	cout << "\t" << "[3]Total Balances." << endl;
	cout << "\t" << "[4]Back To Main Menu." << endl;
	cout << "====================================================" << endl;
}
short ReadNumberFunction()
{
	unsigned short Number = 0;
	cout << "Please Choose Number [1 to 4]: ";
	cin >> Number;

	return Number;
}
bool DepositFunction(vector <stClientData> &vClientData)
{
	stClientData Client;
	double DepositAmount = 0;
	string AccountNumber = "";
	char YesNo = ' ';
	cout << "Please Enter Your Account Number: ";
	getline(cin >> ws, AccountNumber);

	if (FindClientByAccountNumber(AccountNumber, vClientData, Client))
	{
		PrintRecord(Client);
		cout << "Please Enter Deposit Amount" << endl;
		cin >> DepositAmount;
		cout << "Are You Sure You Want To Performe This Transaction ? [Y/N] ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			for (stClientData& C : vClientData)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance += DepositAmount;
					break;
				}
			}
			SaveClientDataToFile(vClientData);
			vClientData = LoadClientDataFromFile("D:\\Coding\\C++\\ClientData.txt");
			cout << "\n";
			cout << "Deposit Had Done Successfully" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Sorry, This Account Number [ " << AccountNumber << " ] is Not Exist" << endl;
		return false;
	}
}
bool WithdrawFunction(vector <stClientData> &vClientData)
{
	stClientData Client;
	double WithdrawAmount = 0;
	string AccountNumber = "";
	char YesNo = ' ';
	cout << "Please Enter Your Account Number: ";
	getline(cin >> ws, AccountNumber);

	if (FindClientByAccountNumber(AccountNumber, vClientData, Client))
	{
		PrintRecord(Client);
		cout << "Please Enter Withdraw Amount" << endl;
		cin >> WithdrawAmount;
		if (Client.AccountBalance < WithdrawAmount)
		{
			cout << "Sorry, You Dont Have This Amount in Your Balance To Withdraw it" << endl;
			return false;
		}
		cout << "Are You Sure You Want To Performe This Transaction ? [Y/N] ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			for (stClientData& C : vClientData)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance -= WithdrawAmount;
					break;
				}
			}
			SaveClientDataToFile(vClientData);
			vClientData = LoadClientDataFromFile("D:\\Coding\\C++\\ClientData.txt");
			cout << "\n";
			cout << "Withdraw Had Done Successfully" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Sorry, This Account Number [ " << AccountNumber << " ] is Not Exist" << endl;
		return false;
	}
}
void DepositScreen()
{
	cout << "===============================================" << endl;
	cout << "                 Deposit Screen                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
}
void WithdrawScreen()
{
	cout << "===============================================" << endl;
	cout << "                 Withdraw Screen                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
}
void TotalBalanceList1(vector <stClientData> vClientData)
{
	cout << "                                      Client List ( " << vClientData.size() << " ) Client(S)." << endl;
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << setw(25) << "| Account Number      | Client Name               | Balance    " << endl;
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
}
void TotalBalanceList2(vector <stClientData> &vClientData)
{
	fstream MyFile;
	vector <string> vString;
	double AmountOfTotalBalance = 0;
	for (stClientData C : vClientData)
	{
		AmountOfTotalBalance += C.AccountBalance;
	}
	MyFile.open("D:\\Coding\\C++\\ClientData.txt", ios::in);
	if (MyFile.is_open())
	{
		string stLine = "";
		while (getline(MyFile, stLine))
		{
			vString = Splite(stLine);
			cout << "| " << left << setw(20) << vString[0] << "| " << setw(20) << vString[1] << "\t  | " << setw(20) << vString[4] << endl;
		}
		cout << endl;
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << "                                          Total Balance = " << AmountOfTotalBalance << "                                          " << endl;
		cout << "\n";
		MyFile.close();
	}
}
void TransactionsFunction(vector <stClientData> &vClientData,vector <stUsers> vUsersData,stUsers UserData)
{
	system("cls");
	TransactionsMenuScreen();
	unsigned short Number = ReadNumberFunction();

	switch (Number)
	{
	case enTransactionsMenu::Deposit:
	{
		system("cls");
		DepositScreen();
		DepositFunction(vClientData);
		cout << "Press Any Key To Go Back To Transactions Menu...";
		system("pause>0");
		TransactionsFunction(vClientData,vUsersData, UserData);
		break;
	}
	case enTransactionsMenu::Withdraw:
	{
		system("cls");
		WithdrawScreen();
		WithdrawFunction(vClientData);
		cout << "Press Any Key To Go Back To Transactions Menu...";
		system("pause>0");
		TransactionsFunction(vClientData,vUsersData, UserData);
		break;
	}
	case enTransactionsMenu::TotalBalances:
	{
		system("cls");
		TotalBalanceList1(vClientData);
		TotalBalanceList2(vClientData);
		cout << "Press Any Key To Go Back To Transactions Menu...";
		system("pause>0");
		TransactionsFunction(vClientData,vUsersData, UserData);
		break;
	}
	case enTransactionsMenu::MainMenu:
	{
		system("cls");
		Start(vClientData,vUsersData,UserData);
		break;
	}
	}
}
short ChooseNumberFunction(string Message)
{
	short ChooseNumber = 0;
	cout << Message << endl;
	cin >> ChooseNumber;

	return ChooseNumber;
}
string ReadString(string Message)
{
	string User;
	cout << Message << endl;
	cin >> User;

	return User;
}
vector <stUsers> LoadUsersDataFromFile(string FilePath)
{
	vector <stUsers> vstUsersData;
	vector <string> sUsersData;
	stUsers UserData;
	fstream MyFile;
	string line = "";
	MyFile.open(FilePath, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			sUsersData = Splite(line);
			if (sUsersData.size() == 3)
			{
				UserData.UserName = sUsersData[0];
				UserData.PassWord = sUsersData[1];
				UserData.Permissions = stoi(sUsersData[2]);
				vstUsersData.push_back(UserData);
			}
		}
		MyFile.close();
	}
	return vstUsersData;
}
bool FindUserByUsername(string Username, vector <stUsers> vUsersDate,stUsers &UserData)
{
	for (stUsers &U : vUsersDate)
	{
		if (U.UserName == Username)
		{
			UserData = U;
			return true;
		}
	}
	return false;
}
bool CheckPassword(string Passwoed, vector <stUsers> vUsersDate)
{
	for (stUsers U : vUsersDate)
	{
		if (U.PassWord == Passwoed)
		{
			return true;
		}
	}
	return false;
}
bool CheckIfUserInSystem(vector <stUsers> vUsersData,stUsers &UserData)
{
	string UserName = ReadString("Enter User Name: ");
	if (!FindUserByUsername(UserName, vUsersData,UserData))
	{
		UserData = UserData;
		cout << "Sorry, This Username [ " << UserName << " ] is Not Exist." << endl;
		return false;
	}
	string PassWord = ReadString("Enter Password: ");
	if (!CheckPassword(PassWord, vUsersData))
	{
		cout << "Sorry, Wrong Password" << endl;
		return false;
	}

	return true;
}
void ManageUsersScreen()
{
	cout << "================================================================================" << endl;
	cout << "                                       Manage Users Screen                         " << endl;
	cout << "================================================================================" << endl;
	cout << "[1] Show Users List." << endl;
	cout << "[2] Add New Users." << endl;
	cout << "[3] Delete Users." << endl;
	cout << "[4] Update Users." << endl;
	cout << "[5] Find Users." << endl;
	cout << "[6] Main Menue." << endl;
	cout << "================================================================================" << endl;
}
void UsersDataList1(vector <stUsers> vUsersData)
{
	cout << "                                      Users List ( " << vUsersData.size() << " ) Users(S)." << endl;
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << setw(25) << "| Username            | Password            | Permission        " << endl;
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
}
void UsersDataList2(string FilePath,vector <stUsers> vUsersDate)
{
	fstream MyFile;
	vector <string> vString;
	MyFile.open(FilePath, ios::in);
	if (MyFile.is_open())
	{
		string stLine = "";
		while (getline(MyFile, stLine))
		{
			vString = Splite(stLine);
			cout << "| " << left << setw(20) << vString[0] << "| " << setw(20) << vString[1] << "| " << setw(20) << vString[2] << endl;
		}
		cout << endl;
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;
		MyFile.close();
	}
}
stUsers ReadUserInfo(string Username)
{
	stUsers Users;
	char YesNo = 'y';
	int counter = 0;
	Users.UserName = Username;
	cout << "Please Enetr Password: " << endl;
	cin >> Users.PassWord;
	cout << "Do You Want To Give Full Access ? (y/n)" << endl;
	cin >> YesNo;
	if (YesNo == 'y' || YesNo == 'Y')
	{
		Users.Permissions = -1;
	}
	else if (YesNo == 'n' || YesNo == 'N')
	{
		cout << "Do You Want To Give Access To: " << endl;
		cout << "\n";
		cout << "Show Client List (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter++;
		}
		cout << "Add New Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 2;
		}
		cout << "Delete Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 4;
		}
		cout << "Update Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 8;
		}
		cout << "Find Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 16;
		}
		cout << "Transactions (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 32;
		}
		cout << "Manage Users (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 64;
		}
	}
	Users.Permissions = counter;
	return Users;
}

string ConvertRecordToUsersLine(stUsers UsersData, string Seperator = "#//#")
{
	string sUsersData = "";

	sUsersData += UsersData.UserName + Seperator;
	sUsersData += UsersData.PassWord + Seperator;
	sUsersData += to_string(UsersData.Permissions);

	return sUsersData;
}
bool AddNewUser(vector <stUsers>& vUsersData)
{
	cout << "===============================================" << endl;
	cout << "                 Add New User                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	stUsers sUsers;
	string Username = "";
	stUsers sUserData;
	cout << "Enter Your Username: " << endl;
	getline(cin >> ws, Username);
	if (FindUserByUsername(Username,vUsersData,sUserData))
	{
		cout << "Sorry This Account Number ( " << Username << " ) is Already Exist" << endl;
		return false;
	}
	stUsers UserData = ReadUserInfo(Username);
	fstream MyFile;
	MyFile.open("D:\\Coding\\C++\\Users.txt", ios::app);
	if (MyFile.is_open())
	{
		string line = ConvertRecordToUsersLine(UserData);
		MyFile << line << endl;
	}
	MyFile.close();
	vUsersData = LoadUsersDataFromFile("D:\\Coding\\C++\\Users.txt");
	cout << endl;
	char YesNo = 'n';
	cout << "User Data Add Successfully, Do You Want To Add Another User ? " << endl;
	if (YesNo == 'y' || YesNo == 'Y')
	{
		AddNewUser(vUsersData);
	}
	cout << endl;
	return true;
}
void PrintUserInfo(stUsers UserData)
{
	cout << "Username: " << UserData.UserName << endl;
	cout << "Password: " << UserData.PassWord << endl;
	cout << "Permission: " << UserData.Permissions << endl;
}
void MarkUserAsDelete(string Username, vector <stUsers>& vUsersData)
{
	for (stUsers& U : vUsersData)
	{
		if (U.UserName == Username)
		{
			U.MarkForDeletion = true;
		}
	}
}
void DeleteUser1(vector <stUsers>& vUsersData)
{
	string stLine = "";
	fstream MyFile;
	MyFile.open("D:\\Coding\\C++\\Users.txt", ios::out);
	if (MyFile.is_open())
	{
		for (stUsers& U : vUsersData)
		{
			if (U.MarkForDeletion == false)
			{
				stLine = ConvertRecordToUsersLine(U);
				MyFile << stLine << endl;
			}
		}
	}
}
bool DeleteUserByUsername(vector <stUsers>& vUsersData)
{
	stUsers UserData;
	char YesNo = ' ';
	string Username = "";
	cout << "===============================================" << endl;
	cout << "                 Delete Client                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << "Please Enter Username : " << endl;
	getline(cin >> ws, Username);
	if (Username == "Admin")
	{
		cout << "Sorry, You Cant Delete The Admin" << endl;
		return false;
	}
	if (FindUserByUsername(Username,vUsersData,UserData))
	{
		cout << "The Following Are User Details : " << endl;
		cout << "\n";
		PrintUserInfo(UserData);
		cout << endl;
		
		cout << "Are You Sure You Want To Delete The User ? (y/n)" << endl;
		cin >> YesNo;

		if (YesNo == 'y' || YesNo == 'Y')
		{
			MarkUserAsDelete(Username, vUsersData);
			DeleteUser1(vUsersData);

			vUsersData = LoadUsersDataFromFile("D:\\Coding\\C++\\Users.txt");
			cout << endl;
			cout << "The User With Username [ " << Username << " ] Has Deleted Successfully" << endl;
			return true;
		}
	}
	else
	{
		cout << "Sorry This Username ( " <<Username << " ) is Not Exist" << endl;
		return false;
	}
}
stUsers ChangeUserInfo()
{
	stUsers Users;
	char YesNo = 'y';
	int counter = 0;
	cout << "Please Enter New Username: " << endl;
	cin >> Users.UserName;
	cout << "Please Enetr New Password: " << endl;
	cin >> Users.PassWord;
	cout << "Do You Want To Give Full Access ? (y/n)" << endl;
	cin >> YesNo;
	if (YesNo == 'y' || YesNo == 'Y')
	{
		Users.Permissions = -1;
	}
	else if (YesNo == 'n' || YesNo == 'N')
	{
		cout << "Do You Want To Give Access To: " << endl;
		cout << "\n";
		cout << "Show Client List (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter++;
		}
		cout << "Add New Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 2;
		}
		cout << "Delete Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 4;
		}
		cout << "Update Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 8;
		}
		cout << "Find Client (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 16;
		}
		cout << "Transactions (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 32;
		}
		cout << "Manage Users (y/n) ? ";
		cin >> YesNo;
		if (YesNo == 'y' || YesNo == 'Y')
		{
			counter += 64;
		}
	}
	Users.Permissions = counter;
	return Users;
}
void SaveUsersDataToFile(vector <stUsers> &vUsersData)
{
	string line = "";
	fstream MyFile;
	MyFile.open("D:\\Coding\\C++\\Users.txt", ios::out);
	if (MyFile.is_open())
	{
		for (stUsers& U : vUsersData)
		{
			line = ConvertRecordToUsersLine(U);
			MyFile << line << endl;
		}
		MyFile.close();
	}
}
bool UpdateUserInfo(vector <stUsers>& vUsersData)
{
	stUsers UserData;
	char YesNo = ' ';
	string Useename = "";
	cout << "===============================================" << endl;
	cout << "                 Update Client                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << "Please Enter Username To Update : " << endl;
	getline(cin >> ws, Useename);
	if (FindUserByUsername(Useename,vUsersData,UserData))
	{
		cout << "The Following Are User Details : " << endl;
		cout << "\n";
		PrintUserInfo(UserData);
		cout << endl;
		cout << "\n";
		cout << "Are You Sure You Want To Update The User ? (Y/N) " << endl;
		cin >> YesNo;
		if (YesNo == 'Y' || YesNo == 'y')
		{
			for (stUsers& U : vUsersData)
			{
				if (U.UserName == Useename)
				{
					U = ChangeUserInfo();
					break;
				}
			}
			SaveUsersDataToFile(vUsersData);
			vUsersData = LoadUsersDataFromFile("D:\\Coding\\C++\\Users.txt");
			cout << endl;
			cout << "Your Info Has Updated Successfully" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Sorry, This User [ " << Useename << " ] is Not Exist" << endl;
		return false;
	}
}
bool FindUserFunction(vector <stUsers> vUsersData)
{
	stUsers UserData;
	string Username = "";
	cout << "===============================================" << endl;
	cout << "                 Find User                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << "Please Enter Your Username : " << endl;
	getline(cin >> ws, Username);
	if (FindUserByUsername(Username,vUsersData,UserData))
	{
		cout << "The Following Are The User Details: " << endl;
		cout << endl;
		PrintUserInfo(UserData);
		return true;
	}
	else
	{
		cout << "Sorry This User ( " << Username << " ) is Not Found" << endl;
		return false;
	}
}
void ManageUsersFunction(vector <stUsers> vUsersDate, vector <stClientData>& vClientData, stUsers UserData)
{
	ManageUsersScreen();
	int Number = ChooseNumberFunction("Choose What Do You Want To Do [1 to 6]: ");
	switch (Number)
	{
	case enManageUsers::UsersList:
	{
		system("cls");
		UsersDataList1(vUsersDate);
		UsersDataList2("D:\\Coding\\C++\\Users.txt", vUsersDate);
		cout << "Press Any Key To Go Back to Main Menu... " << endl;
		system("pause>0");
		system("cls");
		ManageUsersFunction(vUsersDate,vClientData,UserData);
	}
	case enManageUsers::AddUser:
	{
		system("cls");
		AddNewUser(vUsersDate);
		cout << "Press Any Key To Go Back to Main Menu... " << endl;
		system("pause>0");
		system("cls");
		ManageUsersFunction(vUsersDate, vClientData, UserData);
	}
	case enManageUsers::DeleteUser:
	{
		system("cls");
		DeleteUserByUsername(vUsersDate);
		cout << "Press Any Key To Go Back to Main Menu... " << endl;
		system("pause>0");
		system("cls");
		ManageUsersFunction(vUsersDate, vClientData, UserData);
	}
	case enManageUsers::UpdateUser:
	{
		system("cls");
		UpdateUserInfo(vUsersDate);
		cout << "Press Any Key To Go Back to Main Menu... " << endl;
		system("pause>0");
		system("cls");
		ManageUsersFunction(vUsersDate, vClientData, UserData);
	}
	case enManageUsers::FindUser:
	{
		system("cls");
		FindUserFunction(vUsersDate);
		cout << "Press Any Key To Go Back to Main Menu... " << endl;
		system("pause>0");
		system("cls");
		ManageUsersFunction(vUsersDate, vClientData, UserData);
	}
	case enManageUsers::MainMenue:
	{
		system("cls");
		Start(vClientData, vUsersDate, UserData);
	}
	}
}
void Start(vector <stClientData>& vClientData, vector <stUsers>& vUsersData,stUsers UserData)
{
	TheDesign();
	int Number = ChooseNumberFunction("Choose What Do You Want To Do [1 to 7] ? ");
	if (Number == enMenu::ClientList)
	{
		if ((UserData.Permissions & 1))
		{
			system("cls");
			ClientDataList1(vClientData);
			ClientDataList2(vClientData);
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::AddClient)
	{
		if ((UserData.Permissions & 2))
		{
			system("cls");
			AddNewClient(vClientData);
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);

		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::DeleteClient)
	{
		if ((UserData.Permissions & 4))
		{
			system("cls");
			DeleteClientByAccountNumber(vClientData);
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);

		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::UpdateClient)
	{
		if ((UserData.Permissions & 8))
		{
			system("cls");
			UpdateClientInfo(vClientData);
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);


		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::FindClient)
	{
		if ((UserData.Permissions & 16))
		{
			system("cls");
			FindClientFunction(vClientData);
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::Transactions)
	{
		if ((UserData.Permissions & 32))
		{
			system("cls");
			TransactionsFunction(vClientData, vUsersData, UserData);
		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::ManageUsers)
	{
		if ((UserData.Permissions & 32))
		{
			system("cls");
			ManageUsersFunction(vUsersData,vClientData,UserData);

		}
		else
		{
			system("cls");
			cout << "=======================================================" << endl;
			cout << "   You Dont Have Permission Access For This Section   " << endl;
			cout << "=======================================================" << endl;
			cout << endl;
			cout << "Press Any Key To Go Back to Main Menu... " << endl;
			system("pause>0");
			system("cls");
			Start(vClientData, vUsersData, UserData);
		}
	}
	else if (Number == enMenu::Logout)
	{
		system("cls");
		cout << "\n";
		Login();
		system("pause>0");
	}
}
void Login()
{
	stUsers sUserData;
	vector <stClientData> vClientData = LoadClientDataFromFile("D:\\Coding\\C++\\ClientData.txt");
	vector <stUsers> vUsersDate = LoadUsersDataFromFile("D:\\Coding\\C++\\Users.txt");
	cout << "===============================================" << endl;
	cout << "                 Login Screen                    " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	if (CheckIfUserInSystem(vUsersDate,sUserData))
	{
		system("cls");
		Start(vClientData,vUsersDate,sUserData);
	}

}

int main()
{
	Login();

	return 0;
}
