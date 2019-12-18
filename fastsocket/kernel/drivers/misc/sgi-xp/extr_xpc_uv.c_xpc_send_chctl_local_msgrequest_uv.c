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
struct TYPE_2__ {int /*<<< orphan*/ * flags; } ;
struct xpc_partition {int /*<<< orphan*/  chctl_lock; TYPE_1__ chctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_CHCTL_MSGREQUEST ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (struct xpc_partition*) ; 

__attribute__((used)) static void
xpc_send_chctl_local_msgrequest_uv(struct xpc_partition *part, int ch_number)
{
	unsigned long irq_flags;

	spin_lock_irqsave(&part->chctl_lock, irq_flags);
	part->chctl.flags[ch_number] |= XPC_CHCTL_MSGREQUEST;
	spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

	xpc_wakeup_channel_mgr(part);
}