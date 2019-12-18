#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  recvs; } ;
struct rpc_xprt {int /*<<< orphan*/  pending; TYPE_2__* ops; TYPE_1__ stat; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct TYPE_6__ {int len; } ;
struct rpc_rqst {int rq_reply_bytes_recvd; TYPE_3__ rq_private_buf; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  rq_xtime; int /*<<< orphan*/  rq_rtt; int /*<<< orphan*/  rq_xid; struct rpc_xprt* rq_xprt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  xprt_update_rtt (struct rpc_task*) ; 

void xprt_complete_rqst(struct rpc_task *task, int copied)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	dprintk("RPC: %5u xid %08x complete (%d bytes received)\n",
			task->tk_pid, ntohl(req->rq_xid), copied);

	xprt->stat.recvs++;
	req->rq_rtt = ktime_sub(ktime_get(), req->rq_xtime);
	if (xprt->ops->timer != NULL)
		xprt_update_rtt(task);

	list_del_init(&req->rq_list);
	req->rq_private_buf.len = copied;
	/* Ensure all writes are done before we update */
	/* req->rq_reply_bytes_recvd */
	smp_wmb();
	req->rq_reply_bytes_recvd = copied;
	rpc_wake_up_queued_task(&xprt->pending, task);
}