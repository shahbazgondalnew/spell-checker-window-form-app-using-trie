#pragma once
#include<iostream>
#include<string>
#include <msclr\marshal_cppstd.h>
//system string ko std string mien convert krne k liye
#include<fstream>
//file handling
using namespace msclr::interop;
using namespace std;
int sCount = 0;
#define TotalAlpha (26)
#define asciiOfChar(c) ((int)c - (int)'a')
string globalTextIn;
//word written to search
string rightG="";

bool atLeastOne = false;
//atleast one suggestion check
bool addButton = false;
//add button click
bool first = false;
struct nodeOfTrie
{
	nodeOfTrie *nextChar[TotalAlpha];
	bool wordEndBool;
};
 nodeOfTrie *constructNode(void)
{
	nodeOfTrie *pNode = new nodeOfTrie;
	pNode->wordEndBool = false;

	for (int i = 0; i < TotalAlpha; i++)
		pNode->nextChar[i] = NULL;

	return pNode;
}




namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
    nodeOfTrie* root = constructNode();
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;



	public:
		bool replaceEvent = false;
		void mistakeFinder(string givenWord)
		{

			int asci = 97;
			char charr;
			string ret;
			for (int i = 0; i < 26; i++)
			{
				charr = asci;
				ret = charr + givenWord;
				asci++;
				if (search(root, ret) == true)
				{
					cout << ret << " Founded" << endl;
					
					twoWord(globalTextIn, ret);
				}

			}

			asci = 97;
			for (int i = 0; i < 26; i++)
			{

				charr = asci;
				ret = givenWord + charr;


				asci++;
				if (search(root, ret) == true)
				{
					cout << ret << " Founded" << endl;
					twoWord(globalTextIn, ret);
				}
				
				cout << ret << endl;
			}
			asci = 97;
			ret = "";
			int c = 0;
			for (int j = 0; j < 26; j++)
			{
				charr = asci;
				for (int c = 0; c < givenWord.length(); c++)
				{
					ret = "";
					for (int j = 0; j < givenWord.length(); j++)
					{
						if (j == c)
						{
							ret = ret + charr;
						}
						else
						{
							ret = ret + givenWord[j];
						}
					}
					cout << ret << endl;
					if (search(root, ret) == true)
					{
						twoWord(globalTextIn, ret);
						cout << ret << " Founded" << endl;
					}
				}
				asci++;
			}
		}		
		void fileHandlingUpdate(string temp)
		{
			ofstream fileOUT("words_alpha.txt", ios::app); 
			fileOUT <<  endl;
			fileOUT << temp;
			fileOUT.close();
			richTextBox1->Text = "Word Added At The End of File" + "\n";;
		}
		void addWordToDic(string w)
		{
			String^ s = gcnew String(w.c_str());
			if (w =="")
			{
				richTextBox1->Text = "No Word Written" + "\n";;
			}
			if (search(root, w) == true)
			{
				richTextBox1->Text = s+"This word Already Exist" + "\n";;
			}
			else
			{
				insert(root, w);
				richTextBox1->Text = s+" is added sucessfully" + "\n";;
				if (checkBox1->Checked == true)
				{
					fileHandlingUpdate(w);
				}
			}
		}
		void twoWord(string wrong, string right)
		{
			rightG = right;
			for (int i = 0; i < right.length(); i++)
			{
				if (i < wrong.length())
				{
					if (right.at(i) != wrong.at(i))
					{
						String^ strRight1 = gcnew String(right.c_str());
						String^ strWrong1 = gcnew String(wrong.c_str());
						String^ at = "";
						at =  strWrong1[i].ToString();
						String^ with = "";
						with = strRight1[i].ToString();
						richTextBox1->Text ="Replace "+"'" +at+"'" + " with "+ "'" + with+"'"+ " for "+"'"+strRight1+"'"+"\n";
						cout << wrong.at(i) << " Missing at " << i + 1 << endl;
						replaceEvent = true;
						atLeastOne = true;
					}
				}
				else
				{
					String^ strWrong2 = gcnew String(wrong.c_str());
					String^ strRight1 = gcnew String(right.c_str());
					String^ miss = "";
					miss = strRight1[i].ToString();
					richTextBox1->Text = miss + " is missing in '" + strWrong2 + "' for '"+strRight1+"'"+"\n";
					atLeastOne = true;
				}

			}
		}
		bool noMistake(string wordd)
		{
			if (search(root, wordd) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void fileHandlingFIle()
		{
			string wordInsert;
			ifstream inserting;
			inserting.open("words_alpha.txt");
			if (inserting.is_open())
			{
				while (inserting >> wordInsert)
				{
					insert(root, wordInsert);
				}
			}
		}
		string removeGarbage(string given)
		{
			cout << given << endl;
			int o = 0;

			string returnS = given;
			for (int i = 0; i < given.length(); i++)
			{

				int ascii = given.at(i);
				cout << given.at(i) << " is converted with ";
				if ((i == given.length() - 1) && (given.at(i) == ' '))
				{
					cout << "nothing" << endl;
				}
				else if ((i == 0) && (given.at(0) == ' '))
				{

					cout << "with nothing" << endl;

				}

				else if ((ascii > 64) && (ascii < 91))
				{
					ascii += 32;
					char c = ascii;
					cout << c << endl;
					returnS.at(o) = c;
					o++;
				}

				else if ((ascii > 96) && (ascii < 123))
				{
					returnS.at(o) = given.at(i);
					cout << given.at(i) << endl;
					o++;
				}
				else if ((given.at(i) == ' ') && (given.at(i - 1) != ' '))
				{
					returnS.at(o) = given.at(i);
					cout << given.at(i) << endl;
					o++;
				}
				else
				{
					cout << " nothing" << endl;
				}


			}



			return returnS.substr(0, o);
		}
		string removeOnlyText(string given)
		{
			int current = 0;
			for (int i = 0; i < given.length(); i++) {
				if (!isdigit(given[i])) {
					given[current] = given[i];
					current++;
				}
				
			}

			return given.substr(0, current);
		}

		void deleteWord(string w)
		{
			bool action = true;
			root = NULL;
			root = constructNode();
			string wordInsert;
			ifstream inserting;
			inserting.open("words_alpha.txt");
			if (inserting.is_open())
			{
				String^ system_str = gcnew String(w.c_str());
				richTextBox1->Text = system_str + " is Deleted" + "\n";;
				richTextBox1->Text = richTextBox1->Text + "Updating Text File..." + "\n";
				while (inserting >> wordInsert)
				{

					//System::Diagnostics::Debug::WriteLine("Inserting...");
					if (wordInsert != w)
					{
						
						insert(root, wordInsert);

					}
					//
				}
				richTextBox1->Text = system_str + " is Deleted" + "\n";;
				
			}

		}
		void EditWord(string w,string with)
		{
			bool action = true;
			root = NULL;
			root = constructNode();
			string wordInsert;
			ifstream inserting;
			inserting.open("words_alpha.txt");
			if (inserting.is_open())
			{
				String^ system_str = gcnew String(w.c_str());
				//richTextBox1->Text = system_str + " is Deleted" + "\n";;
				richTextBox1->Text =  "Deleted and Updating Text File..." + "\n";
				while (inserting >> wordInsert)
				{

					//System::Diagnostics::Debug::WriteLine("Inserting...");
					if (wordInsert != w)
					{

						insert(root, wordInsert);

					}
					else if (wordInsert == w)
					{
						String^ system_str = gcnew String(w.c_str());
						String^ system_str2 = gcnew String(with.c_str());

						richTextBox1->Text = richTextBox1->Text+ system_str + " is replaced with" +system_str2+ "\n";;
						insert(root,with);
					}

					//

				}
				richTextBox1->Text = system_str + " is Deleted" + "\n";;

			}

		}
		bool search(nodeOfTrie *root, const string key)
		{
			int length = key.length();
			nodeOfTrie *tempNode = root;
			for (int level = 0; level < length; level++)
			{
				int index = asciiOfChar(key[level]);

				if (!tempNode->nextChar[index])
					return false;

				tempNode = tempNode->nextChar[index];
			}

			return (tempNode != NULL && tempNode->wordEndBool);
		}


		void insert(nodeOfTrie *root, const string key)
		{
			nodeOfTrie *tempNode = root;
			for (int level = 0; level < key.length(); level++)
			{
				int index = asciiOfChar(key[level]);
				if (!tempNode->nextChar[index])
					tempNode->nextChar[index] = constructNode();

				tempNode = tempNode->nextChar[index];
			}

			
			tempNode->wordEndBool = true;
		}
		void suggestionsRec(nodeOfTrie* root, string currPrefix)
		{
			if (root->wordEndBool)
			{
				
				if (sCount > 10)
				{
					
					return;
				}
				
				sCount++;
				
					String^ system_str = gcnew String(currPrefix.c_str());
					System::Diagnostics::Debug::WriteLine(system_str);
					richTextBox1->Text = richTextBox1->Text + system_str + "\n";

				
				
				
		
				//cout << endl;
			}

			if (isLastNode(root))
				return;

			for (int i = 0; i < TotalAlpha; i++)
			{
				if (root->nextChar[i])
				{
					
					currPrefix.push_back(97 + i);

					
					suggestionsRec(root->nextChar[i], currPrefix);
					
					currPrefix.pop_back();
				}
			}
		}

		
		int printAutoSuggestions(nodeOfTrie* root, const string givenString)
		{
			nodeOfTrie* tempr = root;

			
			int level;
			int lengthOfStrin = givenString.length();
			for (level = 0; level < lengthOfStrin; level++)
			{
				int index = asciiOfChar(givenString[level]);

				
				if (!tempr->nextChar[index])
					return 0;

				tempr = tempr->nextChar[index];
			}

			
			bool isWord = (tempr->wordEndBool == true);

			
			bool isLast = isLastNode(tempr);

			if (isWord && isLast)
			{
				cout << givenString << endl;
				return -1;
			}

			if (!isLast)
			{
				string prefix = givenString;
				suggestionsRec(tempr, prefix);
				return 1;
			}
		}
		bool isLastNode(struct nodeOfTrie* root)
		{
			for (int i = 0; i < TotalAlpha; i++)
				if (root->nextChar[i])
					return 0;
			return 1;
		}
		string lastWord(string given)
		{
			
			
			
			
			string temp= removeOnlyText(removeGarbage(given));
			given = temp;
			//
			char space = ' ';
			int index = 0;
			bool onlyOne = true;
			string ret = "";
			if (given.length() == 0)
			{

				return given;
			}

			for (int i = 0; i < given.length(); i++)
			{

				if (given.at(i) == space)
				{
					if (i != given.length() - 1)
					{
						index = i;
						onlyOne = false;
					}

				}
			}


			if (onlyOne == true)
			{
				return given;
			}
			else
			{
				for (int i = index + 1; i < given.length(); i++)
				{
					ret = ret + given.at(i);
				}
				return ret;
			}
		}



		Form1(void)
		{
			first = true;
			fileHandlingFIle();

			InitializeComponent();
			
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}



	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
public: System::Windows::Forms::RichTextBox^  richTextBox1;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Button^  button2;

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->AccessibleName = L"searchBox";
			this->textBox1->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(61, 26);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(325, 79);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"\r\nEnter Word Here";
			this->textBox1->Click += gcnew System::EventHandler(this, &Form1::textBox1_Click);
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// richTextBox1
			// 
			this->richTextBox1->AccessibleName = L"suggestionBox";
			this->richTextBox1->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(12, 259);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(517, 256);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->AccessibleName = L"findMistake";
			this->button1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button1->Location = System::Drawing::Point(502, 26);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(93, 33);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Find Mistake";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button2->Location = System::Drawing::Point(502, 65);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(93, 31);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Replace";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::HotTrack;
			this->label1->Font = (gcnew System::Drawing::Font(L"Rockwell", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 205);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(431, 31);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Words Suggestion and Comments";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 148);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 5;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button3->Location = System::Drawing::Point(396, 55);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(93, 50);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Add This Word To Dictionary";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->checkBox1->Location = System::Drawing::Point(392, 32);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(104, 17);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Update Text File";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button4->Location = System::Drawing::Point(502, 102);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(93, 31);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Search";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button5->Location = System::Drawing::Point(502, 139);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(93, 34);
			this->button5->TabIndex = 9;
			this->button5->Text = L"Delete";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button6->Location = System::Drawing::Point(396, 121);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(93, 40);
			this->button6->TabIndex = 10;
			this->button6->Text = L"Edit Word";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->textBox2->Location = System::Drawing::Point(61, 118);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(325, 57);
			this->textBox2->TabIndex = 11;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->label3->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->label3->Location = System::Drawing::Point(8, 55);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(47, 26);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Spell\r\nChecker";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click_1);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ControlText;
			this->label4->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->label4->Location = System::Drawing::Point(8, 135);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(50, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Edit With";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->ClientSize = System::Drawing::Size(643, 527);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		label3->Text = L"Spell\r\nChecker";
		System::String^ textAsString = textBox1->Text;
		std::string AsSTDString= marshal_as<std::string>(textAsString);
		atLeastOne = false;
		AsSTDString = lastWord(AsSTDString);

		richTextBox1->Text = "";//for rset

		if (AsSTDString != "")
		{
			int comp = printAutoSuggestions(root, AsSTDString);
		}
		
		sCount = 0;
		
		

		

		//System::Diagnostics::Debug::WriteLine(textAsString);
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	addButton = false;
	replaceEvent = false;
	
	System::String^ textAsString = textBox1->Text->ToLower();
	std::string AsSTDString = marshal_as<std::string>(textAsString);
	
	
		globalTextIn=AsSTDString;
		globalTextIn= removeOnlyText(removeGarbage(AsSTDString));
		AsSTDString = globalTextIn;
	
	if (noMistake(AsSTDString) == true)
	{
		richTextBox1->Text = "There Is no Mistake";
	}
	else
	{
		if (AsSTDString == "")
		{
			richTextBox1->Text = "Text box is empty or invalid text::KINDLY WRITE SOMETHING";
		}
		if (AsSTDString != "")
		{
			mistakeFinder(AsSTDString);
			if (atLeastOne == false)
			{
				richTextBox1->Text = "There Is no Suggestion::Kindly Add this word";
			}
		}
		
	}
	
	
	
	
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (replaceEvent == true)
	{
		String^ system_str = gcnew String(rightG.c_str());

		textBox1->Text = system_str;

	}
	else
	{
		
		richTextBox1->Text="There is nothing to replace with" + "\n";
	}

	

}
private: System::Void progressBar1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	addButton = true;
	
	System::String^ textAsString = textBox1->Text->ToLower();
	std::string AsSTDString = marshal_as<std::string>(textAsString);

	string temp = lastWord(AsSTDString);
	  string remover = removeOnlyText(removeGarbage(temp));
	  temp = remover;
	if (temp == "")
	{
		richTextBox1->Text = "Text Box is Empty::KINDLY RIGHT SOMETHING" + "\n";
	}
	else if (search(root ,temp)==true)
	{
		richTextBox1->Text = "This word Already exist" + "\n";

	}
	else
	{
		addWordToDic(temp);

	}
	





}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	richTextBox1->Text = "Checked" + "\n";
	
		


}

private: System::Void above_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (first == true)
	{
		textBox1->Text = "";
		first = false;
	}
	

}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	System::String^ textAsString = textBox1->Text->ToLower();
	std::string AsSTDString = marshal_as<std::string>(textAsString);

	string temp = lastWord(AsSTDString);
	if (temp=="")
	{
		richTextBox1->Text = "No Word written" + "\n";
	}
	else if (noMistake(temp) == true)
	{
		richTextBox1->Text ="'"+ textAsString+"'" + " found in dictionary" + "\n";

	}
	else
	{
		richTextBox1->Text = "'"+ textAsString + "'" " not found in dictionary" + "\n";
	}
	
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	System::String^ textAsString = textBox1->Text->ToLower();
	std::string AsSTDString = marshal_as<std::string>(textAsString);

	string temp = lastWord(AsSTDString);
	string remover = removeOnlyText(removeGarbage(temp));
	temp = remover;
	if (temp == "")
	{
		richTextBox1->Text = "Text box is empty or Invalid text::KINDLY WRITE SOMETHING";
	}
	else if (search(root,temp) == false)
	{
		String^ notfounded = gcnew String(temp.c_str());
		richTextBox1->Text =notfounded +" not founded in dictionary" + "\n";
	}
	else
	{
		deleteWord(temp);
	}
	
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	System::String^ textAsString = textBox1->Text->ToLower();
	std::string AsSTDString = marshal_as<std::string>(textAsString);
	System::String^ textAsStringWith = textBox2->Text->ToLower();
	std::string AsSTDStringWith = marshal_as<std::string>(textAsStringWith);
	string temp = lastWord(AsSTDString);
	string remover = removeOnlyText(removeGarbage(temp));
	temp = remover;
	if (AsSTDStringWith == "")
	{
		richTextBox1->Text = "word that going to replace with can not be empty" + "\n";
	}
	else if (AsSTDStringWith == "")
	{
		richTextBox1->Text =   "word replace with can not be empty" + "\n";
	}
	if (noMistake(AsSTDStringWith) == true)
	{
		richTextBox1->Text = "'" + textAsStringWith + "' Already" + " present in dictionary" + "\n";
		richTextBox1->Text = richTextBox1->Text + "Can not Edit it" + "\n";

	}
	if (AsSTDStringWith== AsSTDString)
	{
		richTextBox1->Text = "Both word can not be same" + "\n";
	}

	else
	{
		if (AsSTDStringWith != AsSTDString)
		{
			
			if (AsSTDStringWith != "")
			{
				if (AsSTDString != "")
				{
					if (noMistake(AsSTDStringWith) != true)
					{
						EditWord(AsSTDString, AsSTDStringWith);
					}
				}
			}
		}
	}
	


}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	label3->Text = "Edit this";
}
private: System::Void label3_Click_1(System::Object^  sender, System::EventArgs^  e) {
}
};
}
