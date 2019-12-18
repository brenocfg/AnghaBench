#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  CaList; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ *) ; 
 scalar_t__ CompareX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void AddCa(CEDAR *cedar, X *x)
{
	// Validate arguments
	if (cedar == NULL || x == NULL)
	{
		return;
	}

	LockList(cedar->CaList);
	{
		UINT i;
		bool ok = true;

		for (i = 0;i < LIST_NUM(cedar->CaList);i++)
		{
			X *exist_x = LIST_DATA(cedar->CaList, i);
			if (CompareX(exist_x, x))
			{
				ok = false;
				break;
			}
		}

		if (ok)
		{
			Insert(cedar->CaList, CloneX(x));
		}
	}
	UnlockList(cedar->CaList);
}