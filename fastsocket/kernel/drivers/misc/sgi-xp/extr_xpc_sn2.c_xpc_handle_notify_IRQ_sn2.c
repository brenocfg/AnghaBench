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
typedef  scalar_t__ u64 ;
struct xpc_partition {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 short XP_MAX_NPARTITIONS_SN2 ; 
 int /*<<< orphan*/  xpc_check_for_sent_chctl_flags_sn2 (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 scalar_t__ xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static irqreturn_t
xpc_handle_notify_IRQ_sn2(int irq, void *dev_id)
{
	short partid = (short)(u64)dev_id;
	struct xpc_partition *part = &xpc_partitions[partid];

	DBUG_ON(partid < 0 || partid >= XP_MAX_NPARTITIONS_SN2);

	if (xpc_part_ref(part)) {
		xpc_check_for_sent_chctl_flags_sn2(part);

		xpc_part_deref(part);
	}
	return IRQ_HANDLED;
}