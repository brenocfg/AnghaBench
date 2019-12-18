#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct xpc_partition {scalar_t__ act_state; scalar_t__ reason; TYPE_2__ disengage_timer; scalar_t__ disengage_timeout; int /*<<< orphan*/  act_lock; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_3__ {int /*<<< orphan*/  (* request_partition_deactivation ) (struct xpc_partition*) ;int /*<<< orphan*/  (* request_partition_reactivation ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_partition*,int,int const) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xpc_partition*) ; 
 int /*<<< orphan*/  stub2 (struct xpc_partition*) ; 
 int xpReactivating ; 
 scalar_t__ xpUnloading ; 
 TYPE_1__ xpc_arch_ops ; 
 int xpc_disengage_timelimit ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_partition_going_down (struct xpc_partition*,int) ; 

void
xpc_deactivate_partition(const int line, struct xpc_partition *part,
			 enum xp_retval reason)
{
	unsigned long irq_flags;

	spin_lock_irqsave(&part->act_lock, irq_flags);

	if (part->act_state == XPC_P_AS_INACTIVE) {
		XPC_SET_REASON(part, reason, line);
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
		if (reason == xpReactivating) {
			/* we interrupt ourselves to reactivate partition */
			xpc_arch_ops.request_partition_reactivation(part);
		}
		return;
	}
	if (part->act_state == XPC_P_AS_DEACTIVATING) {
		if ((part->reason == xpUnloading && reason != xpUnloading) ||
		    reason == xpReactivating) {
			XPC_SET_REASON(part, reason, line);
		}
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
		return;
	}

	part->act_state = XPC_P_AS_DEACTIVATING;
	XPC_SET_REASON(part, reason, line);

	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	/* ask remote partition to deactivate with regard to us */
	xpc_arch_ops.request_partition_deactivation(part);

	/* set a timelimit on the disengage phase of the deactivation request */
	part->disengage_timeout = jiffies + (xpc_disengage_timelimit * HZ);
	part->disengage_timer.expires = part->disengage_timeout;
	add_timer(&part->disengage_timer);

	dev_dbg(xpc_part, "bringing partition %d down, reason = %d\n",
		XPC_PARTID(part), reason);

	xpc_partition_going_down(part, reason);
}