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
struct xpc_partition {scalar_t__ act_state; int /*<<< orphan*/  disengage_timer; scalar_t__ disengage_timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cancel_partition_deactivation_request ) (struct xpc_partition*) ;int /*<<< orphan*/  (* assume_partition_disengaged ) (short) ;int /*<<< orphan*/  (* partition_engaged ) (short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 short XPC_PARTID (struct xpc_partition*) ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  del_singleshot_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,short) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  stub1 (short) ; 
 int /*<<< orphan*/  stub2 (short) ; 
 int /*<<< orphan*/  stub3 (struct xpc_partition*) ; 
 scalar_t__ time_is_after_jiffies (scalar_t__) ; 
 TYPE_1__ xpc_arch_ops ; 
 int xpc_disengage_timedout ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (struct xpc_partition*) ; 

int
xpc_partition_disengaged(struct xpc_partition *part)
{
	short partid = XPC_PARTID(part);
	int disengaged;

	disengaged = !xpc_arch_ops.partition_engaged(partid);
	if (part->disengage_timeout) {
		if (!disengaged) {
			if (time_is_after_jiffies(part->disengage_timeout)) {
				/* timelimit hasn't been reached yet */
				return 0;
			}

			/*
			 * Other side hasn't responded to our deactivate
			 * request in a timely fashion, so assume it's dead.
			 */

			dev_info(xpc_part, "deactivate request to remote "
				 "partition %d timed out\n", partid);
			xpc_disengage_timedout = 1;
			xpc_arch_ops.assume_partition_disengaged(partid);
			disengaged = 1;
		}
		part->disengage_timeout = 0;

		/* cancel the timer function, provided it's not us */
		if (!in_interrupt())
			del_singleshot_timer_sync(&part->disengage_timer);

		DBUG_ON(part->act_state != XPC_P_AS_DEACTIVATING &&
			part->act_state != XPC_P_AS_INACTIVE);
		if (part->act_state != XPC_P_AS_INACTIVE)
			xpc_wakeup_channel_mgr(part);

		xpc_arch_ops.cancel_partition_deactivation_request(part);
	}
	return disengaged;
}