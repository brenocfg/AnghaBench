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
struct rpc_xprt {TYPE_1__* ops; int /*<<< orphan*/  task_cleanup; int /*<<< orphan*/  backlog; int /*<<< orphan*/  sending; int /*<<< orphan*/  pending; int /*<<< orphan*/  binding; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct rpc_xprt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*) ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_xprt*) ; 

__attribute__((used)) static void xprt_destroy(struct rpc_xprt *xprt)
{
	dprintk("RPC:       destroying transport %p\n", xprt);
	del_timer_sync(&xprt->timer);

	rpc_destroy_wait_queue(&xprt->binding);
	rpc_destroy_wait_queue(&xprt->pending);
	rpc_destroy_wait_queue(&xprt->sending);
	rpc_destroy_wait_queue(&xprt->backlog);
	cancel_work_sync(&xprt->task_cleanup);
	/*
	 * Tear down transport state and free the rpc_xprt
	 */
	xprt->ops->destroy(xprt);
}