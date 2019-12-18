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
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 scalar_t__ WDOG_PREOP_GIVE_DATA ; 
 scalar_t__ WDOG_PREOP_PANIC ; 
 scalar_t__ WDOG_PRETIMEOUT_NONE ; 
 scalar_t__ atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int data_to_read ; 
 int /*<<< orphan*/  fasync_q ; 
 int /*<<< orphan*/  ipmi_read_lock ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ preaction_val ; 
 int /*<<< orphan*/  preop_panic_excl ; 
 scalar_t__ preop_val ; 
 int pretimeout_since_last_heartbeat ; 
 int /*<<< orphan*/  read_q ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmi_wdog_pretimeout_handler(void *handler_data)
{
	if (preaction_val != WDOG_PRETIMEOUT_NONE) {
		if (preop_val == WDOG_PREOP_PANIC) {
			if (atomic_inc_and_test(&preop_panic_excl))
				panic("Watchdog pre-timeout");
		} else if (preop_val == WDOG_PREOP_GIVE_DATA) {
			spin_lock(&ipmi_read_lock);
			data_to_read = 1;
			wake_up_interruptible(&read_q);
			kill_fasync(&fasync_q, SIGIO, POLL_IN);

			spin_unlock(&ipmi_read_lock);
		}
	}

	/*
	 * On some machines, the heartbeat will give an error and not
	 * work unless we re-enable the timer.  So do so.
	 */
	pretimeout_since_last_heartbeat = 1;
}