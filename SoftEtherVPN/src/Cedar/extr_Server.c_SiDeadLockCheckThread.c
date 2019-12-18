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
struct TYPE_3__ {scalar_t__ HaltDeadLockThread; int /*<<< orphan*/  DeadLockWaitEvent; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  SERVER_DEADLOCK_CHECK_SPAN ; 
 int /*<<< orphan*/  SERVER_DEADLOCK_CHECK_TIMEOUT ; 
 int /*<<< orphan*/  SiCheckDeadLockMain (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SiDeadLockCheckThread(THREAD *t, void *param)
{
	SERVER *s = (SERVER *)param;
	// Validate arguments
	if (s == NULL || t == NULL)
	{
		return;
	}

	while (true)
	{
		Wait(s->DeadLockWaitEvent, SERVER_DEADLOCK_CHECK_SPAN);

		if (s->HaltDeadLockThread)
		{
			break;
		}

		SiCheckDeadLockMain(s, SERVER_DEADLOCK_CHECK_TIMEOUT);
	}
}