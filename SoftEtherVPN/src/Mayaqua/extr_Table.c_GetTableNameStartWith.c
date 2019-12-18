#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {size_t NumTokens; void** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ TABLE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 scalar_t__ Cmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* NullToken () ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 size_t StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/ * TableList ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *GetTableNameStartWith(char *str)
{
	UINT i;
	UINT len;
	LIST *o;
	TOKEN_LIST *t;
	char tmp[MAX_SIZE];
	// Validate arguments
	if (str == NULL)
	{
		return NullToken();
	}

	StrCpy(tmp, sizeof(tmp), str);
	StrUpper(tmp);

	len = StrLen(tmp);

	o = NewListFast(NULL);

	for (i = 0;i < LIST_NUM(TableList);i++)
	{
		TABLE *t = LIST_DATA(TableList, i);
		UINT len2 = StrLen(t->name);

		if (len2 >= len)
		{
			if (Cmp(t->name, tmp, len) == 0)
			{
				Insert(o, CopyStr(t->name));
			}
		}
	}

	t = ZeroMalloc(sizeof(TOKEN_LIST));
	t->NumTokens = LIST_NUM(o);
	t->Token = ZeroMalloc(sizeof(char *) * t->NumTokens);

	for (i = 0;i < t->NumTokens;i++)
	{
		t->Token[i] = LIST_DATA(o, i);
	}

	ReleaseList(o);

	return t;
}