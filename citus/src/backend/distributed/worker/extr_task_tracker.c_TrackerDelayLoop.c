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
 long TaskTrackerDelay ; 
 scalar_t__ got_SIGHUP ; 
 scalar_t__ got_SIGTERM ; 
 int /*<<< orphan*/  pg_usleep (long const) ; 

__attribute__((used)) static void
TrackerDelayLoop(void)
{
	const long SignalCheckInterval = 1000000L; /* check signal every second */

	/*
	 * On some platforms, signals do not interrupt the sleep. To ensure we
	 * respond promptly when someone signals us, we break down the sleep into
	 * 1-second increments, and check for interrupts after each nap.
	 */
	long trackerDelay = TaskTrackerDelay * 1000L;
	while (trackerDelay > (SignalCheckInterval - 1))
	{
		if (got_SIGHUP || got_SIGTERM)
		{
			break;
		}
		pg_usleep(SignalCheckInterval);
		trackerDelay -= SignalCheckInterval;
	}
	if (!(got_SIGHUP || got_SIGTERM))
	{
		pg_usleep(trackerDelay);
	}
}