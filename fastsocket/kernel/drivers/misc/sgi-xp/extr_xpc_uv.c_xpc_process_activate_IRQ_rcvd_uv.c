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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ act_state_req; int /*<<< orphan*/  reason; } ;
struct TYPE_4__ {TYPE_1__ uv; } ;
struct xpc_partition {scalar_t__ act_state; TYPE_2__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int /*<<< orphan*/ ) ; 
 scalar_t__ XPC_P_ASR_ACTIVATE_UV ; 
 scalar_t__ XPC_P_ASR_DEACTIVATE_UV ; 
 scalar_t__ XPC_P_ASR_REACTIVATE_UV ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 short XP_MAX_NPARTITIONS_UV ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xpReactivating ; 
 scalar_t__ xpc_activate_IRQ_rcvd ; 
 int /*<<< orphan*/  xpc_activate_IRQ_rcvd_lock ; 
 int /*<<< orphan*/  xpc_activate_partition (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static void
xpc_process_activate_IRQ_rcvd_uv(void)
{
	unsigned long irq_flags;
	short partid;
	struct xpc_partition *part;
	u8 act_state_req;

	DBUG_ON(xpc_activate_IRQ_rcvd == 0);

	spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
	for (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) {
		part = &xpc_partitions[partid];

		if (part->sn.uv.act_state_req == 0)
			continue;

		xpc_activate_IRQ_rcvd--;
		BUG_ON(xpc_activate_IRQ_rcvd < 0);

		act_state_req = part->sn.uv.act_state_req;
		part->sn.uv.act_state_req = 0;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		if (act_state_req == XPC_P_ASR_ACTIVATE_UV) {
			if (part->act_state == XPC_P_AS_INACTIVE)
				xpc_activate_partition(part);
			else if (part->act_state == XPC_P_AS_DEACTIVATING)
				XPC_DEACTIVATE_PARTITION(part, xpReactivating);

		} else if (act_state_req == XPC_P_ASR_REACTIVATE_UV) {
			if (part->act_state == XPC_P_AS_INACTIVE)
				xpc_activate_partition(part);
			else
				XPC_DEACTIVATE_PARTITION(part, xpReactivating);

		} else if (act_state_req == XPC_P_ASR_DEACTIVATE_UV) {
			XPC_DEACTIVATE_PARTITION(part, part->sn.uv.reason);

		} else {
			BUG();
		}

		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		if (xpc_activate_IRQ_rcvd == 0)
			break;
	}
	spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

}