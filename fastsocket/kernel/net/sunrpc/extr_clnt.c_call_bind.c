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
struct rpc_xprt {TYPE_1__* ops; int /*<<< orphan*/  bind_timeout; } ;
struct rpc_task {int /*<<< orphan*/  tk_timeout; int /*<<< orphan*/  tk_action; struct rpc_xprt* tk_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpcbind ) (struct rpc_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  call_bind_status ; 
 int /*<<< orphan*/  call_connect ; 
 int /*<<< orphan*/  dprint_status (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_bound (struct rpc_xprt*) ; 

__attribute__((used)) static void
call_bind(struct rpc_task *task)
{
	struct rpc_xprt *xprt = task->tk_xprt;

	dprint_status(task);

	task->tk_action = call_connect;
	if (!xprt_bound(xprt)) {
		task->tk_action = call_bind_status;
		task->tk_timeout = xprt->bind_timeout;
		xprt->ops->rpcbind(task);
	}
}