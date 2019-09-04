#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {int /*<<< orphan*/  HubList; } ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_1__*) ; 

void StopAllHub(CEDAR *c)
{
	HUB **hubs;
	UINT i, num;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	LockHubList(c);
	{
		hubs = ToArray(c->HubList);
		num = LIST_NUM(c->HubList);
		DeleteAll(c->HubList);
	}
	UnlockHubList(c);

	for (i = 0;i < num;i++)
	{
		StopHub(hubs[i]);
		ReleaseHub(hubs[i]);
	}

	Free(hubs);
}