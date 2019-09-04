#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bExists; } ;
struct TYPE_4__ {char* pkey; unsigned int weight; } ;
typedef  TYPE_1__ KEYNODE ;

/* Variables and functions */
 unsigned int HashString (char const*,int const) ; 
 unsigned int* TestHashCTable ; 
 unsigned int* TestHashDTable ; 
 TYPE_3__* TestHashTable ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int nMaxStrLen ; 
 unsigned int nTableSize ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 TYPE_1__** test_data ; 

int insert_string(const char *string_in)  
{  
	const int HASH_OFFSET = 0, HASH_C = 1, HASH_D = 2;  
	unsigned int nHash = HashString(string_in, HASH_OFFSET);  
	unsigned int nHashC = HashString(string_in, HASH_C);  
	unsigned int nHashD = HashString(string_in, HASH_D);  
	unsigned int nHashStart = nHash % nTableSize;  
	unsigned int nHashPos = nHashStart;  
	int ln, ires = 0;  

	while (TestHashTable[nHashPos].bExists)  
	{  
		//      if (TestHashCTable[nHashPos]  == (int) nHashC && TestHashDTable[nHashPos] == (int) nHashD)  
		//          break;  
		//      //...  
		//      else  
		//如之前所提示读者的那般，暴雪的Hash算法对于查询那样处理可以，但对插入就不能那么解决  
		nHashPos = (nHashPos + 1) % nTableSize;  

		if (nHashPos == nHashStart)  
			break;  
	}  

	ln = strlen(string_in);  
	if (!TestHashTable[nHashPos].bExists && (ln < nMaxStrLen))  
	{   
		TestHashCTable[nHashPos] = nHashC;  
		TestHashDTable[nHashPos] = nHashD;  

		test_data[nHashPos] = (KEYNODE *) malloc (sizeof(KEYNODE) * 1);  
		if(test_data[nHashPos] == NULL)  
		{  
			printf("10000 EMS ERROR !!!!\n");  
			return 0;  
		}  

		test_data[nHashPos]->pkey = (char *)malloc(ln+1);  
		if(test_data[nHashPos]->pkey == NULL)  
		{  
			printf("10000 EMS ERROR !!!!\n");  
			return 0;  
		}  

		memset(test_data[nHashPos]->pkey, 0, ln+1);  
		strncpy(test_data[nHashPos]->pkey, string_in, ln);  
		*((test_data[nHashPos]->pkey)+ln) = 0;  
		test_data[nHashPos]->weight = nHashPos;  

		TestHashTable[nHashPos].bExists = 1;  
	}  
	else  
	{  
		if(TestHashTable[nHashPos].bExists)  
			printf("30000 in the hash table %s !!!\n", string_in);  
		else  
			printf("90000 strkey error !!!\n");  
	}  
	return nHashPos;  
}