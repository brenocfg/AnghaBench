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
union xpc_channel_ctl_flags {scalar_t__ all_flags; } ;
typedef  scalar_t__ u64 ;
struct xpc_partition_sn2 {int /*<<< orphan*/  remote_GPs_pa; int /*<<< orphan*/  remote_GPs; int /*<<< orphan*/  remote_openclose_args_pa; } ;
struct TYPE_2__ {struct xpc_partition_sn2 sn2; } ;
struct xpc_partition {int /*<<< orphan*/  remote_openclose_args; int /*<<< orphan*/  chctl_lock; union xpc_channel_ctl_flags chctl; TYPE_1__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 int /*<<< orphan*/  XPC_GP_SIZE ; 
 int /*<<< orphan*/  XPC_OPENCLOSE_ARGS_SIZE ; 
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int xpSuccess ; 
 scalar_t__ xpc_any_msg_chctl_flags_set (union xpc_channel_ctl_flags*) ; 
 scalar_t__ xpc_any_openclose_chctl_flags_set (union xpc_channel_ctl_flags*) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int xpc_pull_remote_cachelines_sn2 (struct xpc_partition*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
xpc_get_chctl_all_flags_sn2(struct xpc_partition *part)
{
	struct xpc_partition_sn2 *part_sn2 = &part->sn.sn2;
	unsigned long irq_flags;
	union xpc_channel_ctl_flags chctl;
	enum xp_retval ret;

	/*
	 * See if there are any chctl flags to be handled.
	 */

	spin_lock_irqsave(&part->chctl_lock, irq_flags);
	chctl = part->chctl;
	if (chctl.all_flags != 0)
		part->chctl.all_flags = 0;

	spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

	if (xpc_any_openclose_chctl_flags_set(&chctl)) {
		ret = xpc_pull_remote_cachelines_sn2(part, part->
						     remote_openclose_args,
						     part_sn2->
						     remote_openclose_args_pa,
						     XPC_OPENCLOSE_ARGS_SIZE);
		if (ret != xpSuccess) {
			XPC_DEACTIVATE_PARTITION(part, ret);

			dev_dbg(xpc_chan, "failed to pull openclose args from "
				"partition %d, ret=%d\n", XPC_PARTID(part),
				ret);

			/* don't bother processing chctl flags anymore */
			chctl.all_flags = 0;
		}
	}

	if (xpc_any_msg_chctl_flags_set(&chctl)) {
		ret = xpc_pull_remote_cachelines_sn2(part, part_sn2->remote_GPs,
						     part_sn2->remote_GPs_pa,
						     XPC_GP_SIZE);
		if (ret != xpSuccess) {
			XPC_DEACTIVATE_PARTITION(part, ret);

			dev_dbg(xpc_chan, "failed to pull GPs from partition "
				"%d, ret=%d\n", XPC_PARTID(part), ret);

			/* don't bother processing chctl flags anymore */
			chctl.all_flags = 0;
		}
	}

	return chctl.all_flags;
}