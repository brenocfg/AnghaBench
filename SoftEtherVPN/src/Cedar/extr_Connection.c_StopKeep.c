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
struct TYPE_4__ {int Halt; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  lock; int /*<<< orphan*/  Thread; } ;
typedef  TYPE_1__ KEEP ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void StopKeep(KEEP *k)
{
	// Validate arguments
	if (k == NULL)
	{
		return;
	}

	k->Halt = true;
	Set(k->HaltEvent);
	Cancel(k->Cancel);

	WaitThread(k->Thread, INFINITE);
	ReleaseThread(k->Thread);
	DeleteLock(k->lock);

	ReleaseCancel(k->Cancel);
	ReleaseEvent(k->HaltEvent);

	Free(k);
}