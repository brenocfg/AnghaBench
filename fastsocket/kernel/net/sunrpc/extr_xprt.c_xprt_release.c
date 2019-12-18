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
struct rpc_xprt {TYPE_3__* ops; int /*<<< orphan*/  transport_lock; scalar_t__ idle_timeout; scalar_t__ last_used; int /*<<< orphan*/  timer; int /*<<< orphan*/  recv; struct rpc_task* snd_task; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; TYPE_2__* tk_client; int /*<<< orphan*/  tk_calldata; TYPE_1__* tk_ops; } ;
struct rpc_rqst {int /*<<< orphan*/  (* rq_release_snd_buf ) (struct rpc_rqst*) ;int /*<<< orphan*/ * rq_cred; scalar_t__ rq_buffer; int /*<<< orphan*/  rq_list; struct rpc_xprt* rq_xprt; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* buf_free ) (scalar_t__) ;int /*<<< orphan*/  (* release_request ) (struct rpc_task*) ;int /*<<< orphan*/  (* release_xprt ) (struct rpc_xprt*,struct rpc_task*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  cl_metrics; int /*<<< orphan*/  cl_xprt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rpc_count_stats ) (struct rpc_task*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bc_prealloc (struct rpc_rqst*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_rqst*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ *) ; 
 struct rpc_xprt* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rpc_count_iostats (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  stub3 (struct rpc_task*) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_free_bc_request (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_free_slot (struct rpc_xprt*,struct rpc_rqst*) ; 
 scalar_t__ xprt_has_timer (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_release_write (struct rpc_xprt*,struct rpc_task*) ; 

void xprt_release(struct rpc_task *task)
{
	struct rpc_xprt	*xprt;
	struct rpc_rqst	*req = task->tk_rqstp;

	if (req == NULL) {
		if (task->tk_client) {
			rcu_read_lock();
			xprt = rcu_dereference(task->tk_client->cl_xprt);
			if (xprt->snd_task == task)
				xprt_release_write(xprt, task);
			rcu_read_unlock();
		}
		return;
	}

	xprt = req->rq_xprt;
	if (task->tk_ops->rpc_count_stats != NULL)
		task->tk_ops->rpc_count_stats(task, task->tk_calldata);
	else if (task->tk_client)
		rpc_count_iostats(task, task->tk_client->cl_metrics);
	spin_lock_bh(&xprt->transport_lock);
	xprt->ops->release_xprt(xprt, task);
	if (xprt->ops->release_request)
		xprt->ops->release_request(task);
	if (!list_empty(&req->rq_list))
		list_del(&req->rq_list);
	xprt->last_used = jiffies;
	if (list_empty(&xprt->recv) && xprt_has_timer(xprt))
		mod_timer(&xprt->timer,
				xprt->last_used + xprt->idle_timeout);
	spin_unlock_bh(&xprt->transport_lock);
	if (req->rq_buffer)
		xprt->ops->buf_free(req->rq_buffer);
	if (req->rq_cred != NULL)
		put_rpccred(req->rq_cred);
	task->tk_rqstp = NULL;
	if (req->rq_release_snd_buf)
		req->rq_release_snd_buf(req);

	dprintk("RPC: %5u release request %p\n", task->tk_pid, req);
	if (likely(!bc_prealloc(req)))
		xprt_free_slot(xprt, req);
	else
		xprt_free_bc_request(req);
}