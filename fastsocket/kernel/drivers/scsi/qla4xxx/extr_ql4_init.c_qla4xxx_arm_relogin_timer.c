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
struct ddb_entry {scalar_t__ default_time2wait; int /*<<< orphan*/  retry_relogin_timer; int /*<<< orphan*/  relogin_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 

void qla4xxx_arm_relogin_timer(struct ddb_entry *ddb_entry)
{
	/*
	 * This triggers a relogin.  After the relogin_timer
	 * expires, the relogin gets scheduled.  We must wait a
	 * minimum amount of time since receiving an 0x8014 AEN
	 * with failed device_state or a logout response before
	 * we can issue another relogin.
	 *
	 * Firmware pads this timeout: (time2wait +1).
	 * Driver retry to login should be longer than F/W.
	 * Otherwise F/W will fail
	 * set_ddb() mbx cmd with 0x4005 since it still
	 * counting down its time2wait.
	 */
	atomic_set(&ddb_entry->relogin_timer, 0);
	atomic_set(&ddb_entry->retry_relogin_timer,
		   ddb_entry->default_time2wait + 4);

}