#include <iostream>
using namespace std;
template <class type>
class Node
{
private:
    char name;
    int indexSize; /// size of the linked List of the Node
public:
    int *index;
    Node *Next;
    type *trieNodeChild; ///child
    Node(char name)
    {
        this->name= name;
        indexSize = 0;
        Next=NULL;
        index = NULL;
        trieNodeChild=new type();
    }
    ///setters and getters for Node
    void setindexSize(int indexSize)
    {
        this->indexSize=indexSize;
    }
    int *getindexSize()
    {
        return &indexSize;
    }
    void setname(char name)
    {
        this->name=name;
    }
    char getName()
    {
        return name;
    }
};

template <class type>
class LinkedList
{
private:
    Node<type> *head;
public:
    LinkedList() ///default constructor to initialize  the head to NULL
    {
        head = NULL;
    }
    int* Push_back(Node<type> *node,int element)  /// function to insert element in the end of the given Node's index array , and returns the new array
    {
        int* newArr = new int[*(node->getindexSize()) +1]; /// create new array for indexes with the old size + 1 to insert the new elements
        for (int i = 0; i < *(node->getindexSize()); i++)
        {
            newArr[i] = node->index[i]; /// set old array elements to the new Array
        }
        newArr[*(node->getindexSize())] = element;
        node->setindexSize(*(node->getindexSize())+1); /// incrementing the size of the node's index array by 1
        return newArr;
    }

    type *insertLLNode(char name, int element) /// inserting to the linked List
    {
        Node<type> *newNode = new Node<type>(name);
        if (head == NULL)  /// if the list is empty
        {
            head = newNode; /// then the inserted node is in the head
            head->index = this->Push_back(head,element);
            return head->trieNodeChild;
        }
        Node<type> *Temp = Search(name); /// check if the char is in the linked List
        if (Temp == NULL)  /// then temp is not found in the linked list
        {
            Node<type> *tail;
            tail = head;
            while (tail->Next != NULL)   /// get tail node ,  which its next is NULL because it the last node
            {
                tail = tail->Next;
            }

            tail->Next = newNode;
            newNode->index = Push_back(newNode, element);
            return newNode->trieNodeChild;
        }
        else /// temp is found in the linked list
        {
            Temp->index= this->Push_back(Temp, element); /// we insert the element in the list of temp
            return Temp->trieNodeChild;
        }
    }


    Node<type>*Search(char input)  /// Searching for a char in the Linked List
    {
        Node<type> *TempNode = head;
        while (TempNode != NULL)
        {
            if (input==TempNode->getName())
            {
                return TempNode; ///found char
            }
            else
            {
                TempNode = TempNode->Next;
            }
        }
        return NULL; /// Not Found
    }
};


class TrieNode
{
private:
    LinkedList<TrieNode> *mylist;
public:
    TrieNode()
    {
        mylist= new LinkedList<TrieNode>();

    }
    void insertTrieNode(char *input, int index) /// recursive function for inserting characters
    {
        if (input[index] == '\0') /// base case ,the end of the input
            return;
        TrieNode *node = mylist->insertLLNode(input[index],index);
        node->insertTrieNode(input,index+1);
    }

    Node<TrieNode> *Search(char* input, int index)
    {
        Node<TrieNode> *Temp=mylist->Search(input[index]);
        if( Temp!= NULL)
        {
            if(input[index+1] == NULL)
            {
                return Temp;
            }
            return Temp->trieNodeChild->Search(input,index+1);
        }
        else ///not found
        {
            return NULL;
        }
    }
};

class SuffixTrie
{
private:
    TrieNode root;
public:

    SuffixTrie(char *input)
    {
        this->BuildTrie(input);
    }
    void BuildTrie(char *input) /// function to build the suffix Trie
    {
        for (int i=0 ; input[i] != '\0' ; i++)
        {
            root.insertTrieNode(input, i);
        }
    }

    void Search(char *input)  /// function that Search in the Trie
    {
        Node<TrieNode> *temp = root.Search(input,0);  /// search from 0 because it is the first index
        int length;
        if(temp ==NULL)
        {
            cout<< input<< " not found"<<endl;
        }
        else
        {
            for(length =0; *input != NULL; length++) /// for loop to count the length of the input word
            {
                input+=1;
            }
            for (int i = 0; i < *(temp->getindexSize()); i++)
            {
                int Result =(temp->index[i] - length)+1;
                cout <<Result<<' ';
            }
            cout <<'\n';
        }
    }
};
int main()
{

    SuffixTrie t("bananabanaba$");
    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
    t.Search("anana");// prints 1
    return 0;
}
