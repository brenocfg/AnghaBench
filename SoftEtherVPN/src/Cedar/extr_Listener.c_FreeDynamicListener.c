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
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * Listener; } ;
typedef  TYPE_1__ DYNAMIC_LISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void FreeDynamicListener(DYNAMIC_LISTENER *d)
{
	// Validate arguments
	if (d == NULL)
	{
		return;
	}

	Lock(d->Lock);
	{
		if (d->Listener != NULL)
		{
			StopListener(d->Listener);
			ReleaseListener(d->Listener);
			d->Listener = NULL;
		}
	}
	Unlock(d->Lock);

	ReleaseCedar(d->Cedar);

	DeleteLock(d->Lock);

	Free(d);
}