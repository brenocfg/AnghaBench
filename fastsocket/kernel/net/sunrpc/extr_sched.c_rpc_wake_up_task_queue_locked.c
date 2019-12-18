#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rpc_wait_queue {int dummy; } ;
struct rpc_task {struct rpc_wait_queue* tk_waitqueue; } ;

/* Variables and functions */
 scalar_t__ RPC_IS_QUEUED (struct rpc_task*) ; 
 int /*<<< orphan*/  __rpc_do_wake_up_task (struct rpc_wait_queue*,struct rpc_task*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void rpc_wake_up_task_queue_locked(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	if (RPC_IS_QUEUED(task)) {
		smp_rmb();
		if (task->tk_waitqueue == queue)
			__rpc_do_wake_up_task(queue, task);
	}
}