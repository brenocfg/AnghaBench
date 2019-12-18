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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/  ref; } ;
struct TYPE_9__ {int /*<<< orphan*/  PoolWaitList; scalar_t__ PoolHalting; } ;
typedef  TYPE_1__ THREAD ;
typedef  TYPE_2__ EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* NewEvent () ; 
 int /*<<< orphan*/  ReleaseEvent (TYPE_2__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int Wait (TYPE_2__*,int /*<<< orphan*/ ) ; 

bool WaitThread(THREAD *t, UINT timeout)
{
	bool ret = false;
	EVENT *e = NULL;
	// Validate arguments
	if (t == NULL)
	{
		return false;
	}

	LockList(t->PoolWaitList);
	{
		if (t->PoolHalting)
		{
			// Has already been stopped
			ret = true;
		}
		else
		{
			// Register the completion notifying event to the list
			e = NewEvent();
			AddRef(e->ref);
			Insert(t->PoolWaitList, e);
		}
	}
	UnlockList(t->PoolWaitList);

	if (e != NULL)
	{
		// Wait Event
		ret = Wait(e, timeout);

		LockList(t->PoolWaitList);
		{
			if (Delete(t->PoolWaitList, e))
			{
				ReleaseEvent(e);
			}
		}
		UnlockList(t->PoolWaitList);

		ReleaseEvent(e);
	}

	return ret;
}