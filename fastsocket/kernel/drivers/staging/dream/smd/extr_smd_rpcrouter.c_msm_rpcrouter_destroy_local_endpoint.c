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
struct TYPE_2__ {int /*<<< orphan*/  cid; int /*<<< orphan*/  pid; } ;
union rr_control_msg {TYPE_1__ cli; int /*<<< orphan*/  cmd; } ;
struct msm_rpc_endpoint {int /*<<< orphan*/  list; int /*<<< orphan*/  read_q_wake_lock; int /*<<< orphan*/  cid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCROUTER_CTRL_CMD_REMOVE_CLIENT ; 
 int /*<<< orphan*/  RR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msm_rpc_endpoint*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int rpcrouter_send_control_msg (union rr_control_msg*) ; 
 int /*<<< orphan*/  wake_lock_destroy (int /*<<< orphan*/ *) ; 

int msm_rpcrouter_destroy_local_endpoint(struct msm_rpc_endpoint *ept)
{
	int rc;
	union rr_control_msg msg;

	msg.cmd = RPCROUTER_CTRL_CMD_REMOVE_CLIENT;
	msg.cli.pid = ept->pid;
	msg.cli.cid = ept->cid;

	RR("x REMOVE_CLIENT id=%d:%08x\n", ept->pid, ept->cid);
	rc = rpcrouter_send_control_msg(&msg);
	if (rc < 0)
		return rc;

	wake_lock_destroy(&ept->read_q_wake_lock);
	list_del(&ept->list);
	kfree(ept);
	return 0;
}