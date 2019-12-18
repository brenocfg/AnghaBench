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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  NotifyCancelList; } ;
typedef  TYPE_1__ CLIENT ;
typedef  int /*<<< orphan*/  CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiNotifyInternal(CLIENT *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// Set all the notification event
	LockList(c->NotifyCancelList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(c->NotifyCancelList);i++)
		{
			CANCEL *cancel = LIST_DATA(c->NotifyCancelList, i);
			Cancel(cancel);
		}
	}
	UnlockList(c->NotifyCancelList);
}