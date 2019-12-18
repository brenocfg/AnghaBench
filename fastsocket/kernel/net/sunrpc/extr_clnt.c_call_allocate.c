#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_xprt {TYPE_4__* ops; } ;
struct TYPE_7__ {struct rpc_procinfo* rpc_proc; } ;
struct rpc_task {void (* tk_action ) (struct rpc_task*) ;int /*<<< orphan*/  tk_pid; scalar_t__ tk_status; TYPE_3__ tk_msg; struct rpc_xprt* tk_xprt; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {scalar_t__ rq_callsize; scalar_t__ rq_rcvsize; int /*<<< orphan*/ * rq_buffer; TYPE_2__* rq_cred; } ;
struct rpc_procinfo {scalar_t__ p_proc; scalar_t__ p_arglen; scalar_t__ p_replen; int /*<<< orphan*/ * p_decode; } ;
struct TYPE_8__ {int /*<<< orphan*/ * (* buf_alloc ) (struct rpc_task*,int) ;} ;
struct TYPE_6__ {TYPE_1__* cr_auth; } ;
struct TYPE_5__ {unsigned int au_cslack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int HZ ; 
 scalar_t__ RPC_CALLHDRSIZE ; 
 scalar_t__ RPC_IS_ASYNC (struct rpc_task*) ; 
 scalar_t__ RPC_REPHDRSIZE ; 
 void call_bind (struct rpc_task*) ; 
 int /*<<< orphan*/  dprint_status (struct rpc_task*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_delay (struct rpc_task*,int) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signalled () ; 
 int /*<<< orphan*/ * stub1 (struct rpc_task*,int) ; 

__attribute__((used)) static void
call_allocate(struct rpc_task *task)
{
	unsigned int slack = task->tk_rqstp->rq_cred->cr_auth->au_cslack;
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = task->tk_xprt;
	struct rpc_procinfo *proc = task->tk_msg.rpc_proc;

	dprint_status(task);

	task->tk_status = 0;
	task->tk_action = call_bind;

	if (req->rq_buffer)
		return;

	if (proc->p_proc != 0) {
		BUG_ON(proc->p_arglen == 0);
		if (proc->p_decode != NULL)
			BUG_ON(proc->p_replen == 0);
	}

	/*
	 * Calculate the size (in quads) of the RPC call
	 * and reply headers, and convert both values
	 * to byte sizes.
	 */
	req->rq_callsize = RPC_CALLHDRSIZE + (slack << 1) + proc->p_arglen;
	req->rq_callsize <<= 2;
	req->rq_rcvsize = RPC_REPHDRSIZE + slack + proc->p_replen;
	req->rq_rcvsize <<= 2;

	req->rq_buffer = xprt->ops->buf_alloc(task,
					req->rq_callsize + req->rq_rcvsize);
	if (req->rq_buffer != NULL)
		return;

	dprintk("RPC: %5u rpc_buffer allocation failed\n", task->tk_pid);

	if (RPC_IS_ASYNC(task) || !signalled()) {
		task->tk_action = call_allocate;
		rpc_delay(task, HZ>>4);
		return;
	}

	rpc_exit(task, -ERESTARTSYS);
}