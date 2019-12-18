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
struct rpc_task {int /*<<< orphan*/ * tk_action; int /*<<< orphan*/  tk_calldata; TYPE_1__* tk_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_call_done ) (struct rpc_task*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ASSASSINATED (struct rpc_task*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_release (struct rpc_task*) ; 

void rpc_exit_task(struct rpc_task *task)
{
	task->tk_action = NULL;
	if (task->tk_ops->rpc_call_done != NULL) {
		task->tk_ops->rpc_call_done(task, task->tk_calldata);
		if (task->tk_action != NULL) {
			WARN_ON(RPC_ASSASSINATED(task));
			/* Always release the RPC slot and buffer memory */
			xprt_release(task);
		}
	}
}