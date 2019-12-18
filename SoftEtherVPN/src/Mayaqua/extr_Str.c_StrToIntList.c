#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  InsertIntDistinct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsEmptyStr (char*) ; 
 scalar_t__ IsNum (char*) ; 
 int /*<<< orphan*/ * NewIntList (int) ; 
 TYPE_1__* ParseTokenWithoutNullStr (char*,char*) ; 
 int /*<<< orphan*/  ToInt (char*) ; 

LIST *StrToIntList(char *str, bool sorted)
{
	LIST *o;
	TOKEN_LIST *t;

	o = NewIntList(sorted);

	t = ParseTokenWithoutNullStr(str, " ,/;\t");

	if (t != NULL)
	{
		UINT i;

		for (i = 0;i < t->NumTokens;i++)
		{
			char *s = t->Token[i];

			if (IsEmptyStr(s) == false)
			{
				if (IsNum(s))
				{
					InsertIntDistinct(o, ToInt(s));
				}
			}
		}

		FreeToken(t);
	}

	return o;
}