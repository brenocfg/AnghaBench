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
struct TYPE_3__ {scalar_t__ remote_act_state; } ;
struct TYPE_4__ {TYPE_1__ uv; } ;
struct xpc_partition {int /*<<< orphan*/  reason; TYPE_2__ sn; } ;
struct xpc_activate_mq_msg_deactivate_req_uv {int /*<<< orphan*/  reason; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_ACTIVATE_MQ_MSG_DEACTIVATE_REQ_UV ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  xpc_send_activate_IRQ_part_uv (struct xpc_partition*,struct xpc_activate_mq_msg_deactivate_req_uv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_request_partition_deactivation_uv(struct xpc_partition *part)
{
	struct xpc_activate_mq_msg_deactivate_req_uv msg;

	/*
	 * ??? Is it a good idea to make this conditional on what is
	 * ??? potentially stale state information?
	 */
	if (part->sn.uv.remote_act_state != XPC_P_AS_DEACTIVATING &&
	    part->sn.uv.remote_act_state != XPC_P_AS_INACTIVE) {

		msg.reason = part->reason;
		xpc_send_activate_IRQ_part_uv(part, &msg, sizeof(msg),
					 XPC_ACTIVATE_MQ_MSG_DEACTIVATE_REQ_UV);
	}
}