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
struct TYPE_2__ {void* vers; void* prog; int /*<<< orphan*/  cid; int /*<<< orphan*/  pid; int /*<<< orphan*/  cmd; } ;
union rr_control_msg {TYPE_1__ srv; } ;
typedef  void* uint32_t ;
struct rr_server {int dummy; } ;
struct msm_rpc_endpoint {int /*<<< orphan*/  cid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RPCROUTER_CTRL_CMD_NEW_SERVER ; 
 int /*<<< orphan*/  RR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 struct rr_server* rpcrouter_create_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int rpcrouter_send_control_msg (union rr_control_msg*) ; 

int msm_rpc_register_server(struct msm_rpc_endpoint *ept,
			    uint32_t prog, uint32_t vers)
{
	int rc;
	union rr_control_msg msg;
	struct rr_server *server;

	server = rpcrouter_create_server(ept->pid, ept->cid,
					 prog, vers);
	if (!server)
		return -ENODEV;

	msg.srv.cmd = RPCROUTER_CTRL_CMD_NEW_SERVER;
	msg.srv.pid = ept->pid;
	msg.srv.cid = ept->cid;
	msg.srv.prog = prog;
	msg.srv.vers = vers;

	RR("x NEW_SERVER id=%d:%08x prog=%08x:%08x\n",
	   ept->pid, ept->cid, prog, vers);

	rc = rpcrouter_send_control_msg(&msg);
	if (rc < 0)
		return rc;

	return 0;
}