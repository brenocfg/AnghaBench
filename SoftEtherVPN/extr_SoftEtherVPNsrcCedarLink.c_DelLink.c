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
struct TYPE_3__ {int /*<<< orphan*/  LinkList; } ;
typedef  int /*<<< orphan*/  LINK ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 scalar_t__ Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseLink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void DelLink(HUB *hub, LINK *k)
{
	// Validate arguments
	if (hub == NULL || k == NULL)
	{
		return;
	}

	LockList(hub->LinkList);
	{
		if (Delete(hub->LinkList, k))
		{
			ReleaseLink(k);
		}
	}
	UnlockList(hub->LinkList);
}