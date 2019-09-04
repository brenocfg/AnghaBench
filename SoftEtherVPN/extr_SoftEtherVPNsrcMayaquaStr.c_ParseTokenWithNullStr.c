#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_10__ {scalar_t__ Buf; } ;
struct TYPE_9__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 char* DefaultTokenSplitChars () ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsCharInStr (char*,char) ; 
 int /*<<< orphan*/  LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* NullToken () ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 size_t StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,char*,int) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *ParseTokenWithNullStr(char *str, char *split_chars)
{
	LIST *o;
	UINT i, len;
	BUF *b;
	char zero = 0;
	TOKEN_LIST *t;
	// Validate arguments
	if (str == NULL)
	{
		return NullToken();
	}
	if (split_chars == NULL)
	{
		split_chars = DefaultTokenSplitChars();
	}

	b = NewBuf();
	o = NewListFast(NULL);

	len = StrLen(str);

	for (i = 0;i < (len + 1);i++)
	{
		char c = str[i];
		bool flag = IsCharInStr(split_chars, c);

		if (c == '\0')
		{
			flag = true;
		}

		if (flag == false)
		{
			WriteBuf(b, &c, sizeof(char));
		}
		else
		{
			WriteBuf(b, &zero, sizeof(char));

			Insert(o, CopyStr((char *)b->Buf));
			ClearBuf(b);
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
	FreeBuf(b);

	return t;
}