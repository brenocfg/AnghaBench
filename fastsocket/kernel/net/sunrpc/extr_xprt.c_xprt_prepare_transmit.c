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
struct rpc_task {int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int rq_reply_bytes_recvd; int /*<<< orphan*/  rq_bytes_sent; struct rpc_xprt* rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reserve_xprt ) (struct rpc_xprt*,struct rpc_task*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,struct rpc_task*) ; 

int xprt_prepare_transmit(struct rpc_task *task)
{
	struct rpc_rqst	*req = task->tk_rqstp;
	struct rpc_xprt	*xprt = req->rq_xprt;
	int err = 0;

	dprintk("RPC: %5u xprt_prepare_transmit\n", task->tk_pid);

	spin_lock_bh(&xprt->transport_lock);
	if (req->rq_reply_bytes_recvd && !req->rq_bytes_sent) {
		err = req->rq_reply_bytes_recvd;
		goto out_unlock;
	}
	if (!xprt->ops->reserve_xprt(xprt, task))
		err = -EAGAIN;
out_unlock:
	spin_unlock_bh(&xprt->transport_lock);
	return err;
}