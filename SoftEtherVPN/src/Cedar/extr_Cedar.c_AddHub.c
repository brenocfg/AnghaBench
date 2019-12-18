#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ HUB ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IsHub (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (TYPE_2__*) ; 
 scalar_t__ MAX_HUBS ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_2__*) ; 

void AddHub(CEDAR *c, HUB *h)
{
	// Validate arguments
	if (c == NULL || h == NULL)
	{
		return;
	}

	LockHubList(c);
	{
#if	0
		// We shall not check here the number of hub
		if (LIST_NUM(c->HubList) >= MAX_HUBS)
		{
			// over limit
			UnlockHubList(c);
			return;
		}
#endif

		// Confirm there is no hub which have same name
		if (IsHub(c, h->Name))
		{
			// exist
			UnlockHubList(c);
			return;
		}

		// Register the hub
		Insert(c->HubList, h);
		AddRef(h->ref);
	}
	UnlockHubList(c);
}