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
struct rpc_task_setup {int flags; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; struct rpc_clnt* rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {struct rpc_cred* rpc_cred; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct rpc_clnt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_default_ops ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  rpcproc_null ; 

struct rpc_task *rpc_call_null(struct rpc_clnt *clnt, struct rpc_cred *cred, int flags)
{
	struct rpc_message msg = {
		.rpc_proc = &rpcproc_null,
		.rpc_cred = cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clnt,
		.rpc_message = &msg,
		.callback_ops = &rpc_default_ops,
		.flags = flags,
	};
	return rpc_run_task(&task_setup_data);
}