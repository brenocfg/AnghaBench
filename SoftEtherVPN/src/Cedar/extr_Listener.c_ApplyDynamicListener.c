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
struct TYPE_3__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/ * Listener; int /*<<< orphan*/  Port; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Cedar; scalar_t__* EnablePtr; } ;
typedef  TYPE_1__ DYNAMIC_LISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHERE ; 

void ApplyDynamicListener(DYNAMIC_LISTENER *d)
{
	// Validate arguments
	if (d == NULL)
	{
		return;
	}

	Lock(d->Lock);
	{
		// Change the state
		if (*d->EnablePtr)
		{
			if (d->Listener == NULL)
			{
				// Create a listener
				WHERE;
				d->Listener = NewListener(d->Cedar, d->Protocol, d->Port);
			}
		}
		else
		{
			// Stop the listener
			if (d->Listener != NULL)
			{
				WHERE;
				StopListener(d->Listener);
				ReleaseListener(d->Listener);
				d->Listener = NULL;
			}
		}
	}
	Unlock(d->Lock);
}