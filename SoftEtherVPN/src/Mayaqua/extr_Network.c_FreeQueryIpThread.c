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
struct TYPE_4__ {int Halt; int /*<<< orphan*/  Lock; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  Thread; } ;
typedef  TYPE_1__ QUERYIPTHREAD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeQueryIpThread(QUERYIPTHREAD *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	t->Halt = true;
	Set(t->HaltEvent);

	WaitThread(t->Thread, INFINITE);
	ReleaseThread(t->Thread);

	ReleaseEvent(t->HaltEvent);

	DeleteLock(t->Lock);

	Free(t);
}