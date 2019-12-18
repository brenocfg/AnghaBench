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
struct TYPE_4__ {TYPE_1__* rpc_proc; } ;
struct rpc_task {int /*<<< orphan*/  tk_start; scalar_t__ tk_timeouts; TYPE_2__ tk_msg; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rtt; int /*<<< orphan*/  rq_xtime; scalar_t__ rq_reply_bytes_recvd; scalar_t__ rq_xmit_bytes_sent; scalar_t__ rq_ntrans; } ;
struct rpc_iostats {void* om_execute; void* om_rtt; void* om_queue; int /*<<< orphan*/  om_bytes_recv; int /*<<< orphan*/  om_bytes_sent; int /*<<< orphan*/  om_timeouts; int /*<<< orphan*/  om_ntrans; int /*<<< orphan*/  om_ops; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {size_t p_statidx; } ;

/* Variables and functions */
 void* ktime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rpc_count_iostats(const struct rpc_task *task, struct rpc_iostats *stats)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_iostats *op_metrics;
	ktime_t delta;

	if (!stats || !req)
		return;

	op_metrics = &stats[task->tk_msg.rpc_proc->p_statidx];

	op_metrics->om_ops++;
	op_metrics->om_ntrans += req->rq_ntrans;
	op_metrics->om_timeouts += task->tk_timeouts;

	op_metrics->om_bytes_sent += req->rq_xmit_bytes_sent;
	op_metrics->om_bytes_recv += req->rq_reply_bytes_recvd;

	delta = ktime_sub(req->rq_xtime, task->tk_start);
	op_metrics->om_queue = ktime_add(op_metrics->om_queue, delta);

	op_metrics->om_rtt = ktime_add(op_metrics->om_rtt, req->rq_rtt);

	delta = ktime_sub(ktime_get(), task->tk_start);
	op_metrics->om_execute = ktime_add(op_metrics->om_execute, delta);
}