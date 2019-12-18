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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; TYPE_1__* ops; } ;
struct rpc_task {int /*<<< orphan*/  tk_status; int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_reply_bytes_recvd; struct rpc_xprt* rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* timer ) (struct rpc_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*) ; 

__attribute__((used)) static void xprt_timer(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	if (task->tk_status != -ETIMEDOUT)
		return;
	dprintk("RPC: %5u xprt_timer\n", task->tk_pid);

	spin_lock_bh(&xprt->transport_lock);
	if (!req->rq_reply_bytes_recvd) {
		if (xprt->ops->timer)
			xprt->ops->timer(task);
	} else
		task->tk_status = 0;
	spin_unlock_bh(&xprt->transport_lock);
}