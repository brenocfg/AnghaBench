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
struct TYPE_10__ {TYPE_1__* Switch; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  L3DeleteOldArpTable (TYPE_2__*) ; 
 int /*<<< orphan*/  L3DeleteOldIpWaitList (TYPE_2__*) ; 
 int /*<<< orphan*/  L3PollingArpWaitTable (TYPE_2__*) ; 
 int /*<<< orphan*/  L3PollingBeacon (TYPE_2__*) ; 
 int /*<<< orphan*/  L3PollingIpQueue (TYPE_2__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void L3Polling(L3IF *f)
{
	L3SW *s;
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	s = f->Switch;

	// Lock the entire switch in the middle of the polling process
	Lock(s->lock);
	{
		// Beacon transmission
		L3PollingBeacon(f);

		// Process the IP queue
		L3PollingIpQueue(f);

		// Clear old ARP table entries
		L3DeleteOldArpTable(f);

		// Polling ARP resolution waiting list
		L3PollingArpWaitTable(f);

		// Clear the IP waiting list
		L3DeleteOldIpWaitList(f);
	}
	Unlock(s->lock);
}