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
struct TYPE_4__ {int /*<<< orphan*/  HubList; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int IsHub (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool IsHubExistsWithLock(CEDAR *cedar, char *hubname)
{
	bool ret = false;
	// Validate arguments
	if (cedar == NULL || hubname == NULL)
	{
		return false;
	}

	LockList(cedar->HubList);
	{
		ret = IsHub(cedar, hubname);
	}
	UnlockList(cedar->HubList);

	return ret;
}