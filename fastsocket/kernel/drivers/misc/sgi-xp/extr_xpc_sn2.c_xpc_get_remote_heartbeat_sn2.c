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
struct xpc_vars_sn2 {scalar_t__ heartbeat; int /*<<< orphan*/ * heartbeating_to_mask; int /*<<< orphan*/  heartbeat_offline; } ;
struct TYPE_3__ {int /*<<< orphan*/  remote_vars_pa; } ;
struct TYPE_4__ {TYPE_1__ sn2; } ;
struct xpc_partition {scalar_t__ last_heartbeat; TYPE_2__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 int /*<<< orphan*/  XPC_RP_VARS_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_partition_id ; 
 int xpNoHeartbeat ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xp_pa (struct xpc_vars_sn2*) ; 
 int xp_remote_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_hb_allowed_sn2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpc_part ; 
 scalar_t__ xpc_remote_copy_buffer_sn2 ; 

__attribute__((used)) static enum xp_retval
xpc_get_remote_heartbeat_sn2(struct xpc_partition *part)
{
	struct xpc_vars_sn2 *remote_vars;
	enum xp_retval ret;

	remote_vars = (struct xpc_vars_sn2 *)xpc_remote_copy_buffer_sn2;

	/* pull the remote vars structure that contains the heartbeat */
	ret = xp_remote_memcpy(xp_pa(remote_vars),
			       part->sn.sn2.remote_vars_pa,
			       XPC_RP_VARS_SIZE);
	if (ret != xpSuccess)
		return ret;

	dev_dbg(xpc_part, "partid=%d, heartbeat=%lld, last_heartbeat=%lld, "
		"heartbeat_offline=%lld, HB_mask[0]=0x%lx\n", XPC_PARTID(part),
		remote_vars->heartbeat, part->last_heartbeat,
		remote_vars->heartbeat_offline,
		remote_vars->heartbeating_to_mask[0]);

	if ((remote_vars->heartbeat == part->last_heartbeat &&
	    !remote_vars->heartbeat_offline) ||
	    !xpc_hb_allowed_sn2(sn_partition_id,
				remote_vars->heartbeating_to_mask)) {
		ret = xpNoHeartbeat;
	} else {
		part->last_heartbeat = remote_vars->heartbeat;
	}

	return ret;
}