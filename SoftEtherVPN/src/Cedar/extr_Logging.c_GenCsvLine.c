#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_8__ {scalar_t__ Buf; } ;
struct TYPE_7__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/  ReplaceForCsv (char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,char*,int) ; 

char *GenCsvLine(TOKEN_LIST *t)
{
	UINT i;
	BUF *b;
	char *ret;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	b = NewBuf();
	for (i = 0;i < t->NumTokens;i++)
	{
		if (t->Token[i] != NULL)
		{
			ReplaceForCsv(t->Token[i]);
			if (StrLen(t->Token[i]) == 0)
			{
				WriteBuf(b, "-", 1);
			}
			else
			{
				WriteBuf(b, t->Token[i], StrLen(t->Token[i]));
			}
		}
		else
		{
			WriteBuf(b, "-", 1);
		}
		if (i != (t->NumTokens - 1))
		{
			WriteBuf(b, ",", 1);
		}
	}
	WriteBuf(b, "\0", 1);

	ret = (char *)b->Buf;

	Free(b);

	return ret;
}