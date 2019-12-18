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
struct xpc_partition {scalar_t__ act_state; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {int (* get_remote_heartbeat ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int stub1 (struct xpc_partition*) ; 
 int xpSuccess ; 
 short xp_max_npartitions ; 
 short xp_partition_id ; 
 TYPE_1__ xpc_arch_ops ; 
 scalar_t__ xpc_exiting ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static void
xpc_check_remote_hb(void)
{
	struct xpc_partition *part;
	short partid;
	enum xp_retval ret;

	for (partid = 0; partid < xp_max_npartitions; partid++) {

		if (xpc_exiting)
			break;

		if (partid == xp_partition_id)
			continue;

		part = &xpc_partitions[partid];

		if (part->act_state == XPC_P_AS_INACTIVE ||
		    part->act_state == XPC_P_AS_DEACTIVATING) {
			continue;
		}

		ret = xpc_arch_ops.get_remote_heartbeat(part);
		if (ret != xpSuccess)
			XPC_DEACTIVATE_PARTITION(part, ret);
	}
}