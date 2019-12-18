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
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  SockEvent2; int /*<<< orphan*/  SockEvent1; int /*<<< orphan*/  Event2; int /*<<< orphan*/  Event1; } ;
typedef  TYPE_1__ TUBEPAIR_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 

void CleanupTubePairData(TUBEPAIR_DATA *d)
{
	// Validate arguments
	if (d == NULL)
	{
		return;
	}

	ReleaseEvent(d->Event1);
	ReleaseEvent(d->Event2);

	ReleaseSockEvent(d->SockEvent1);
	ReleaseSockEvent(d->SockEvent2);

	DeleteLock(d->Lock);

	Free(d);
}