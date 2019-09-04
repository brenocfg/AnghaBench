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
struct TYPE_5__ {int /*<<< orphan*/  HubList; } ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 scalar_t__ Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockHubList (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_1__*) ; 

void DelHubEx(CEDAR *c, HUB *h, bool no_lock)
{
	// Validate arguments
	if (c == NULL || h == NULL)
	{
		return;
	}

	if (no_lock == false)
	{
		LockHubList(c);
	}

	if (Delete(c->HubList, h))
	{
		ReleaseHub(h);
	}

	if (no_lock == false)
	{
		UnlockHubList(c);
	}
}