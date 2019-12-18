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
struct TYPE_4__ {scalar_t__ NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 scalar_t__ IsInList (int /*<<< orphan*/ *,void*) ; 
 int IsNum (char*) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_PUBLIC_PORT_NUM ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 size_t ToInt (char*) ; 

LIST *StrToPortList(char *str)
{
	LIST *o;
	TOKEN_LIST *t;
	UINT i;
	if (str == NULL)
	{
		return NULL;
	}

	// Convert to token
	t = ParseToken(str, ", ");
	if (t == NULL)
	{
		return NULL;
	}
	if (t->NumTokens == 0)
	{
		FreeToken(t);
		return NULL;
	}

	o = NewListFast(NULL);

	for (i = 0;i < t->NumTokens;i++)
	{
		char *s = t->Token[i];
		UINT n;
		if (IsNum(s) == false)
		{
			ReleaseList(o);
			FreeToken(t);
			return NULL;
		}
		n = ToInt(s);
		if (n == 0 || n >= 65536)
		{
			ReleaseList(o);
			FreeToken(t);
			return NULL;
		}
		if (IsInList(o, (void *)n))
		{
			ReleaseList(o);
			FreeToken(t);
			return NULL;
		}
		Add(o, (void *)n);
	}

	FreeToken(t);

	if (LIST_NUM(o) > MAX_PUBLIC_PORT_NUM)
	{
		ReleaseList(o);
		return NULL;
	}

	return o;
}