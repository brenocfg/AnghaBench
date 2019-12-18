#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rpc_cred; } ;
struct rpc_task {int tk_status; int /*<<< orphan*/  tk_pid; TYPE_5__* tk_rqstp; int /*<<< orphan*/  tk_flags; TYPE_1__ tk_msg; } ;
struct rpc_cred {TYPE_4__* cr_ops; TYPE_3__* cr_auth; } ;
struct TYPE_10__ {struct rpc_cred* rq_cred; } ;
struct TYPE_9__ {int (* crrefresh ) (struct rpc_task*) ;} ;
struct TYPE_8__ {TYPE_2__* au_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  au_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_cred*) ; 
 int rpcauth_bindcred (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct rpc_task*) ; 

int
rpcauth_refreshcred(struct rpc_task *task)
{
	struct rpc_cred	*cred;
	int err;

	cred = task->tk_rqstp->rq_cred;
	if (cred == NULL) {
		err = rpcauth_bindcred(task, task->tk_msg.rpc_cred, task->tk_flags);
		if (err < 0)
			goto out;
		cred = task->tk_rqstp->rq_cred;
	};
	dprintk("RPC: %5u refreshing %s cred %p\n",
		task->tk_pid, cred->cr_auth->au_ops->au_name, cred);

	err = cred->cr_ops->crrefresh(task);
out:
	if (err < 0)
		task->tk_status = err;
	return err;
}