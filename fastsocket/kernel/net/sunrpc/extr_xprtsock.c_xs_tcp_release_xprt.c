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
struct rpc_xprt {struct rpc_task* snd_task; } ;
struct rpc_task {TYPE_2__* tk_xprt; struct rpc_rqst* tk_rqstp; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct rpc_rqst {scalar_t__ rq_bytes_sent; TYPE_1__ rq_snd_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CLOSE_WAIT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_release_xprt (struct rpc_xprt*,struct rpc_task*) ; 

__attribute__((used)) static void xs_tcp_release_xprt(struct rpc_xprt *xprt, struct rpc_task *task)
{
	struct rpc_rqst *req;

	if (task != xprt->snd_task)
		return;
	if (task == NULL)
		goto out_release;
	req = task->tk_rqstp;
	if (req == NULL)
		goto out_release;
	if (req->rq_bytes_sent == 0)
		goto out_release;
	if (req->rq_bytes_sent == req->rq_snd_buf.len)
		goto out_release;
	set_bit(XPRT_CLOSE_WAIT, &task->tk_xprt->state);
out_release:
	xprt_release_xprt(xprt, task);
}