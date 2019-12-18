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
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {struct rpc_cred* rq_cred; } ;
struct rpc_cred {TYPE_1__* cr_ops; } ;
struct TYPE_2__ {struct rpc_cred* (* crbind ) (struct rpc_task*,struct rpc_cred*,int) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rpc_cred*) ; 
 int PTR_ERR (struct rpc_cred*) ; 
 int RPCAUTH_LOOKUP_NEW ; 
 int RPC_TASK_ASYNC ; 
 int RPC_TASK_ROOTCREDS ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rpcauth_bind_new_cred (struct rpc_task*,int) ; 
 struct rpc_cred* rpcauth_bind_root_cred (struct rpc_task*,int) ; 
 struct rpc_cred* stub1 (struct rpc_task*,struct rpc_cred*,int) ; 

__attribute__((used)) static int
rpcauth_bindcred(struct rpc_task *task, struct rpc_cred *cred, int flags)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_cred *new;
	int lookupflags = 0;

	if (flags & RPC_TASK_ASYNC)
		lookupflags |= RPCAUTH_LOOKUP_NEW;
	if (cred != NULL)
		new = cred->cr_ops->crbind(task, cred, lookupflags);
	else if (flags & RPC_TASK_ROOTCREDS)
		new = rpcauth_bind_root_cred(task, lookupflags);
	else
		new = rpcauth_bind_new_cred(task, lookupflags);
	if (IS_ERR(new))
		return PTR_ERR(new);
	if (req->rq_cred != NULL)
		put_rpccred(req->rq_cred);
	req->rq_cred = new;
	return 0;
}