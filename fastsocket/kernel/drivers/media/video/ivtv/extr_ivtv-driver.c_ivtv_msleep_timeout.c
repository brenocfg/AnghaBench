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
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int msecs_to_jiffies (unsigned int) ; 
 int schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int signal_pending (int /*<<< orphan*/ ) ; 

int ivtv_msleep_timeout(unsigned int msecs, int intr)
{
	int timeout = msecs_to_jiffies(msecs);

	do {
		set_current_state(intr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		timeout = schedule_timeout(timeout);
		if (intr) {
			int ret = signal_pending(current);

			if (ret)
				return ret;
		}
	} while (timeout);
	return 0;
}