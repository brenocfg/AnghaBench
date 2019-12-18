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
struct TYPE_4__ {int Halt; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  lock; int /*<<< orphan*/  Thread; int /*<<< orphan*/  Sock; } ;
typedef  TYPE_1__ FARM_CONTROLLER ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SiStopConnectToController(FARM_CONTROLLER *f)
{
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	f->Halt = true;

	// Stop the connection
	Lock(f->lock);
	{
		Disconnect(f->Sock);
	}
	Unlock(f->lock);

	Set(f->HaltEvent);

	// Wait for the thread termination
	WaitThread(f->Thread, INFINITE);
	ReleaseThread(f->Thread);

	DeleteLock(f->lock);
	ReleaseEvent(f->HaltEvent);

	Free(f);
}