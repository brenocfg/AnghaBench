#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union xpc_channel_ctl_flags {int /*<<< orphan*/  all_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  all_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_chctl_amo_va; } ;
struct TYPE_5__ {TYPE_1__ sn2; } ;
struct xpc_partition {int /*<<< orphan*/  chctl_lock; TYPE_3__ chctl; TYPE_2__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_receive_IRQ_amo_sn2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (struct xpc_partition*) ; 

__attribute__((used)) static void
xpc_check_for_sent_chctl_flags_sn2(struct xpc_partition *part)
{
	union xpc_channel_ctl_flags chctl;
	unsigned long irq_flags;

	chctl.all_flags = xpc_receive_IRQ_amo_sn2(part->sn.sn2.
						  local_chctl_amo_va);
	if (chctl.all_flags == 0)
		return;

	spin_lock_irqsave(&part->chctl_lock, irq_flags);
	part->chctl.all_flags |= chctl.all_flags;
	spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

	dev_dbg(xpc_chan, "received notify IRQ from partid=%d, chctl.all_flags="
		"0x%llx\n", XPC_PARTID(part), chctl.all_flags);

	xpc_wakeup_channel_mgr(part);
}