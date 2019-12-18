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
struct TYPE_4__ {scalar_t__ value; int /*<<< orphan*/  offline; } ;
struct xpc_partition_uv {TYPE_2__ cached_heartbeat; int /*<<< orphan*/  heartbeat_gpa; } ;
struct TYPE_3__ {struct xpc_partition_uv uv; } ;
struct xpc_partition {scalar_t__ last_heartbeat; TYPE_1__ sn; } ;
struct xpc_heartbeat_uv {int dummy; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  uv_gpa (TYPE_2__*) ; 
 int xpNoHeartbeat ; 
 int xpSuccess ; 
 int xp_remote_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum xp_retval
xpc_get_remote_heartbeat_uv(struct xpc_partition *part)
{
	struct xpc_partition_uv *part_uv = &part->sn.uv;
	enum xp_retval ret;

	ret = xp_remote_memcpy(uv_gpa(&part_uv->cached_heartbeat),
			       part_uv->heartbeat_gpa,
			       sizeof(struct xpc_heartbeat_uv));
	if (ret != xpSuccess)
		return ret;

	if (part_uv->cached_heartbeat.value == part->last_heartbeat &&
	    !part_uv->cached_heartbeat.offline) {

		ret = xpNoHeartbeat;
	} else {
		part->last_heartbeat = part_uv->cached_heartbeat.value;
	}
	return ret;
}