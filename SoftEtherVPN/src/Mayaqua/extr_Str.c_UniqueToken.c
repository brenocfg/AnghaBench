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
struct TYPE_4__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *UniqueToken(TOKEN_LIST *t)
{
	UINT i, num, j, n;
	TOKEN_LIST *ret;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	num = 0;
	for (i = 0;i < t->NumTokens;i++)
	{
		bool exists = false;

		for (j = 0;j < i;j++)
		{
			if (StrCmpi(t->Token[j], t->Token[i]) == 0)
			{
				exists = true;
				break;
			}
		}

		if (exists == false)
		{
			num++;
		}
	}

	ret = ZeroMalloc(sizeof(TOKEN_LIST));
	ret->Token = ZeroMalloc(sizeof(char *) * num);
	ret->NumTokens = num;

	n = 0;

	for (i = 0;i < t->NumTokens;i++)
	{
		bool exists = false;

		for (j = 0;j < i;j++)
		{
			if (StrCmpi(t->Token[j], t->Token[i]) == 0)
			{
				exists = true;
				break;
			}
		}

		if (exists == false)
		{
			ret->Token[n++] = CopyStr(t->Token[i]);
		}
	}

	return ret;
}