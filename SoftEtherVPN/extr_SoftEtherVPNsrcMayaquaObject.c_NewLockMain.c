#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AbortExitEx (char*) ; 
 int /*<<< orphan*/  OBJECT_ALLOC_FAIL_SLEEP_TIME ; 
 scalar_t__ OBJECT_ALLOC__MAX_RETRY ; 
 int /*<<< orphan*/ * OSNewLock () ; 
 int /*<<< orphan*/  SleepThread (int /*<<< orphan*/ ) ; 

LOCK *NewLockMain()
{
	LOCK *lock;
	UINT retry = 0;

	while (true)
	{
		if ((retry++) > OBJECT_ALLOC__MAX_RETRY)
		{
			AbortExitEx("error: OSNewLock() failed.\n\n");
		}
		lock = OSNewLock();
		if (lock != NULL)
		{
			break;
		}
		SleepThread(OBJECT_ALLOC_FAIL_SLEEP_TIME);
	}

	return lock;
}