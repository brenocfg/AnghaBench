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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  size_t UINT ;
struct TYPE_4__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_1__* GetPackElementNames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SeekBufToBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDynListValue (char*,int /*<<< orphan*/ ) ; 

void AddDynList(BUF *b)
{
	PACK *p;
	TOKEN_LIST *t;
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	SeekBufToBegin(b);

	p = BufToPack(b);
	if (p == NULL)
	{
		return;
	}

	t = GetPackElementNames(p);
	if (t != NULL)
	{
		UINT i;

		for (i = 0;i < t->NumTokens;i++)
		{
			char *name = t->Token[i];
			UINT64 v = PackGetInt64(p, name);

			SetDynListValue(name, v);
		}

		FreeToken(t);
	}

	FreePack(p);
}