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
struct TYPE_4__ {int /*<<< orphan*/  L3SwList; } ;
typedef  int /*<<< orphan*/  L3SW ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * L3GetSw (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  L3SwStop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseL3Sw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool L3DelSw(CEDAR *c, char *name)
{
	L3SW *s;
	bool ret = false;
	// Validate arguments
	if (c == NULL || name == NULL)
	{
		return false;
	}

	LockList(c->L3SwList);
	{
		s = L3GetSw(c, name);

		if (s != NULL)
		{
			// Stop and delete
			L3SwStop(s);
			Delete(c->L3SwList, s);
			ReleaseL3Sw(s);
			ReleaseL3Sw(s);

			ret = true;
		}
	}
	UnlockList(c->L3SwList);

	return ret;
}