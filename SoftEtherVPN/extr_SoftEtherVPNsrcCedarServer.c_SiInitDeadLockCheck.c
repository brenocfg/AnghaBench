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
struct TYPE_4__ {int HaltDeadLockThread; int /*<<< orphan*/  DeadLockCheckThread; int /*<<< orphan*/  DeadLockWaitEvent; scalar_t__ DisableDeadLockCheck; } ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SiDeadLockCheckThread ; 

void SiInitDeadLockCheck(SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}
	if (s->DisableDeadLockCheck)
	{
		return;
	}

	s->HaltDeadLockThread = false;
	s->DeadLockWaitEvent = NewEvent();
	s->DeadLockCheckThread = NewThread(SiDeadLockCheckThread, s);
}