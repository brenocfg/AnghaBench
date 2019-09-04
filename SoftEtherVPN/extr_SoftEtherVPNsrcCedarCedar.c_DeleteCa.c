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
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TO_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool DeleteCa(CEDAR *cedar, UINT ptr)
{
	bool b = false;
	// Validate arguments
	if (cedar == NULL || ptr == 0)
	{
		return false;
	}

	LockList(cedar->CaList);
	{
		UINT i;

		for (i = 0;i < LIST_NUM(cedar->CaList);i++)
		{
			X *x = LIST_DATA(cedar->CaList, i);

			if (POINTER_TO_KEY(x) == ptr)
			{
				Delete(cedar->CaList, x);
				FreeX(x);

				b = true;

				break;
			}
		}
	}
	UnlockList(cedar->CaList);

	return b;
}