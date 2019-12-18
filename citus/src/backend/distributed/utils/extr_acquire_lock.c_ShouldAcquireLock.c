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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  PG_WAIT_EXTENSION ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_TIMEOUT ; 
 int WaitLatch (int /*<<< orphan*/ ,int,long,int /*<<< orphan*/ ) ; 
 scalar_t__ got_sigterm ; 
 int /*<<< orphan*/  proc_exit (int) ; 

__attribute__((used)) static bool
ShouldAcquireLock(long sleepms)
{
	int rc;

	/* early escape in case we already got the signal to stop acquiring the lock */
	if (got_sigterm)
	{
		return false;
	}

	rc = WaitLatch(MyLatch, WL_LATCH_SET | WL_TIMEOUT | WL_POSTMASTER_DEATH,
				   sleepms * 1L, PG_WAIT_EXTENSION);
	ResetLatch(MyLatch);

	/* emergency bailout if postmaster has died */
	if (rc & WL_POSTMASTER_DEATH)
	{
		proc_exit(1);
	}

	CHECK_FOR_INTERRUPTS();

	return !got_sigterm;
}