#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xpc_partition {scalar_t__ act_state; unsigned long disengage_timeout; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {int (* any_partition_engaged ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 unsigned long XPC_DEACTIVATE_PRINTMSG_INTERVAL ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_shub () ; 
 scalar_t__ is_uv () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int stub1 () ; 
 int stub2 () ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  unregister_die_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_sysctl_table (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int xpUnloading ; 
 short xp_max_npartitions ; 
 int /*<<< orphan*/  xpc_activate_IRQ_wq ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_clear_interface () ; 
 int /*<<< orphan*/  xpc_die_notifier ; 
 int /*<<< orphan*/  xpc_discovery_exited ; 
 scalar_t__ xpc_disengage_timedout ; 
 int /*<<< orphan*/  xpc_exit_sn2 () ; 
 int /*<<< orphan*/  xpc_exit_uv () ; 
 int xpc_exiting ; 
 int /*<<< orphan*/  xpc_hb_checker_exited ; 
 int /*<<< orphan*/  xpc_part ; 
 scalar_t__ xpc_partition_disengaged (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 
 int /*<<< orphan*/  xpc_reboot_notifier ; 
 scalar_t__ xpc_sysctl ; 
 int /*<<< orphan*/  xpc_teardown_partitions () ; 
 int /*<<< orphan*/  xpc_teardown_rsvd_page () ; 

__attribute__((used)) static void
xpc_do_exit(enum xp_retval reason)
{
	short partid;
	int active_part_count, printed_waiting_msg = 0;
	struct xpc_partition *part;
	unsigned long printmsg_time, disengage_timeout = 0;

	/* a 'rmmod XPC' and a 'reboot' cannot both end up here together */
	DBUG_ON(xpc_exiting == 1);

	/*
	 * Let the heartbeat checker thread and the discovery thread
	 * (if one is running) know that they should exit. Also wake up
	 * the heartbeat checker thread in case it's sleeping.
	 */
	xpc_exiting = 1;
	wake_up_interruptible(&xpc_activate_IRQ_wq);

	/* wait for the discovery thread to exit */
	wait_for_completion(&xpc_discovery_exited);

	/* wait for the heartbeat checker thread to exit */
	wait_for_completion(&xpc_hb_checker_exited);

	/* sleep for a 1/3 of a second or so */
	(void)msleep_interruptible(300);

	/* wait for all partitions to become inactive */

	printmsg_time = jiffies + (XPC_DEACTIVATE_PRINTMSG_INTERVAL * HZ);
	xpc_disengage_timedout = 0;

	do {
		active_part_count = 0;

		for (partid = 0; partid < xp_max_npartitions; partid++) {
			part = &xpc_partitions[partid];

			if (xpc_partition_disengaged(part) &&
			    part->act_state == XPC_P_AS_INACTIVE) {
				continue;
			}

			active_part_count++;

			XPC_DEACTIVATE_PARTITION(part, reason);

			if (part->disengage_timeout > disengage_timeout)
				disengage_timeout = part->disengage_timeout;
		}

		if (xpc_arch_ops.any_partition_engaged()) {
			if (time_is_before_jiffies(printmsg_time)) {
				dev_info(xpc_part, "waiting for remote "
					 "partitions to deactivate, timeout in "
					 "%ld seconds\n", (disengage_timeout -
					 jiffies) / HZ);
				printmsg_time = jiffies +
				    (XPC_DEACTIVATE_PRINTMSG_INTERVAL * HZ);
				printed_waiting_msg = 1;
			}

		} else if (active_part_count > 0) {
			if (printed_waiting_msg) {
				dev_info(xpc_part, "waiting for local partition"
					 " to deactivate\n");
				printed_waiting_msg = 0;
			}

		} else {
			if (!xpc_disengage_timedout) {
				dev_info(xpc_part, "all partitions have "
					 "deactivated\n");
			}
			break;
		}

		/* sleep for a 1/3 of a second or so */
		(void)msleep_interruptible(300);

	} while (1);

	DBUG_ON(xpc_arch_ops.any_partition_engaged());

	xpc_teardown_rsvd_page();

	if (reason == xpUnloading) {
		(void)unregister_die_notifier(&xpc_die_notifier);
		(void)unregister_reboot_notifier(&xpc_reboot_notifier);
	}

	/* clear the interface to XPC's functions */
	xpc_clear_interface();

	if (xpc_sysctl)
		unregister_sysctl_table(xpc_sysctl);

	xpc_teardown_partitions();

	if (is_shub())
		xpc_exit_sn2();
	else if (is_uv())
		xpc_exit_uv();
}