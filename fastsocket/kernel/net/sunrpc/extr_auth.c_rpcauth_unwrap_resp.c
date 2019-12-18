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
struct rpc_task {int /*<<< orphan*/  tk_pid; TYPE_1__* tk_rqstp; } ;
struct rpc_cred {TYPE_2__* cr_ops; } ;
typedef  int (* kxdrproc_t ) (void*,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int (* crunwrap_resp ) (struct rpc_task*,int (*) (void*,int /*<<< orphan*/ *,void*),void*,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  cr_name; } ;
struct TYPE_3__ {struct rpc_cred* rq_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_cred*) ; 
 int stub1 (struct rpc_task*,int (*) (void*,int /*<<< orphan*/ *,void*),void*,int /*<<< orphan*/ *,void*) ; 

int
rpcauth_unwrap_resp(struct rpc_task *task, kxdrproc_t decode, void *rqstp,
		__be32 *data, void *obj)
{
	struct rpc_cred *cred = task->tk_rqstp->rq_cred;

	dprintk("RPC: %5u using %s cred %p to unwrap rpc data\n",
			task->tk_pid, cred->cr_ops->cr_name, cred);
	if (cred->cr_ops->crunwrap_resp)
		return cred->cr_ops->crunwrap_resp(task, decode, rqstp,
						   data, obj);
	/* By default, we decode the arguments normally. */
	return decode(rqstp, data, obj);
}