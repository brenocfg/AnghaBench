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
struct xpc_partition_sn2 {int /*<<< orphan*/  activate_IRQ_phys_cpuid; int /*<<< orphan*/  activate_IRQ_nasid; int /*<<< orphan*/  remote_amos_page_pa; } ;
struct TYPE_2__ {struct xpc_partition_sn2 sn2; } ;
struct xpc_partition {scalar_t__ act_state; int reason; TYPE_1__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  cnodeid_to_nasid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ sn_register_xp_addr_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xpPhysAddrRegFailed ; 
 int xpRetry ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xpc_part ; 
 int xpc_pull_remote_vars_part_sn2 (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_send_activate_IRQ_sn2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum xp_retval
xpc_make_first_contact_sn2(struct xpc_partition *part)
{
	struct xpc_partition_sn2 *part_sn2 = &part->sn.sn2;
	enum xp_retval ret;

	/*
	 * Register the remote partition's amos with SAL so it can handle
	 * and cleanup errors within that address range should the remote
	 * partition go down. We don't unregister this range because it is
	 * difficult to tell when outstanding writes to the remote partition
	 * are finished and thus when it is safe to unregister. This should
	 * not result in wasted space in the SAL xp_addr_region table because
	 * we should get the same page for remote_amos_page_pa after module
	 * reloads and system reboots.
	 */
	if (sn_register_xp_addr_region(part_sn2->remote_amos_page_pa,
				       PAGE_SIZE, 1) < 0) {
		dev_warn(xpc_part, "xpc_activating(%d) failed to register "
			 "xp_addr region\n", XPC_PARTID(part));

		ret = xpPhysAddrRegFailed;
		XPC_DEACTIVATE_PARTITION(part, ret);
		return ret;
	}

	/*
	 * Send activate IRQ to get other side to activate if they've not
	 * already begun to do so.
	 */
	xpc_send_activate_IRQ_sn2(part_sn2->remote_amos_page_pa,
				  cnodeid_to_nasid(0),
				  part_sn2->activate_IRQ_nasid,
				  part_sn2->activate_IRQ_phys_cpuid);

	while ((ret = xpc_pull_remote_vars_part_sn2(part)) != xpSuccess) {
		if (ret != xpRetry) {
			XPC_DEACTIVATE_PARTITION(part, ret);
			return ret;
		}

		dev_dbg(xpc_part, "waiting to make first contact with "
			"partition %d\n", XPC_PARTID(part));

		/* wait a 1/4 of a second or so */
		(void)msleep_interruptible(250);

		if (part->act_state == XPC_P_AS_DEACTIVATING)
			return part->reason;
	}

	return xpSuccess;
}