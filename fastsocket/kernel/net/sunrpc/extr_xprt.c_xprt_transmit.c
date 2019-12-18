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
struct TYPE_10__ {scalar_t__ qlen; } ;
struct TYPE_9__ {int max_slots; int /*<<< orphan*/  pending_u; int /*<<< orphan*/  sending_u; int /*<<< orphan*/  bklog_u; scalar_t__ recvs; scalar_t__ sends; int /*<<< orphan*/  req_u; } ;
struct TYPE_8__ {scalar_t__ qlen; } ;
struct TYPE_7__ {scalar_t__ qlen; } ;
struct rpc_xprt {int /*<<< orphan*/  transport_lock; TYPE_5__ pending; TYPE_4__ stat; TYPE_3__ sending; TYPE_2__ backlog; int /*<<< orphan*/  num_reqs; TYPE_1__* ops; int /*<<< orphan*/  connect_cookie; int /*<<< orphan*/  timer; int /*<<< orphan*/  recv; } ;
struct rpc_task {int tk_status; int /*<<< orphan*/  tk_flags; int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_reply_bytes_recvd; int /*<<< orphan*/  rq_xtime; int /*<<< orphan*/  rq_connect_cookie; int /*<<< orphan*/  rq_bytes_sent; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  rq_rcv_buf; int /*<<< orphan*/  rq_private_buf; int /*<<< orphan*/  rq_slen; struct rpc_xprt* rq_xprt; } ;
struct TYPE_6__ {int (* send_request ) (struct rpc_task*) ;int /*<<< orphan*/  (* set_retrans_timeout ) (struct rpc_task*) ;} ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  RPC_TASK_SENT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_singleshot_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ rpc_reply_expected (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_sleep_on (TYPE_5__*,struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct rpc_task*) ; 
 int /*<<< orphan*/  stub2 (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_reset_majortimeo (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_timer ; 

void xprt_transmit(struct rpc_task *task)
{
	struct rpc_rqst	*req = task->tk_rqstp;
	struct rpc_xprt	*xprt = req->rq_xprt;
	int status, numreqs;

	dprintk("RPC: %5u xprt_transmit(%u)\n", task->tk_pid, req->rq_slen);

	if (!req->rq_reply_bytes_recvd) {
		if (list_empty(&req->rq_list) && rpc_reply_expected(task)) {
			/*
			 * Add to the list only if we're expecting a reply
			 */
			spin_lock_bh(&xprt->transport_lock);
			/* Update the softirq receive buffer */
			memcpy(&req->rq_private_buf, &req->rq_rcv_buf,
					sizeof(req->rq_private_buf));
			/* Add request to the receive list */
			list_add_tail(&req->rq_list, &xprt->recv);
			spin_unlock_bh(&xprt->transport_lock);
			xprt_reset_majortimeo(req);
			/* Turn off autodisconnect */
			del_singleshot_timer_sync(&xprt->timer);
		}
	} else if (!req->rq_bytes_sent)
		return;

	req->rq_connect_cookie = xprt->connect_cookie;
	req->rq_xtime = ktime_get();
	status = xprt->ops->send_request(task);
	if (status != 0) {
		task->tk_status = status;
		return;
	}

	dprintk("RPC: %5u xmit complete\n", task->tk_pid);
	task->tk_flags |= RPC_TASK_SENT;
	spin_lock_bh(&xprt->transport_lock);

	xprt->ops->set_retrans_timeout(task);

	numreqs = atomic_read(&xprt->num_reqs);
	if (numreqs > xprt->stat.max_slots)
		xprt->stat.max_slots = numreqs;
	xprt->stat.sends++;
	xprt->stat.req_u += xprt->stat.sends - xprt->stat.recvs;
	xprt->stat.bklog_u += xprt->backlog.qlen;
	xprt->stat.sending_u += xprt->sending.qlen;
	xprt->stat.pending_u += xprt->pending.qlen;

	/* Don't race with disconnect */
	if (!xprt_connected(xprt))
		task->tk_status = -ENOTCONN;
	else if (!req->rq_reply_bytes_recvd && rpc_reply_expected(task)) {
		/*
		 * Sleep on the pending queue since
		 * we're expecting a reply.
		 */
		rpc_sleep_on(&xprt->pending, task, xprt_timer);
	}
	spin_unlock_bh(&xprt->transport_lock);
}