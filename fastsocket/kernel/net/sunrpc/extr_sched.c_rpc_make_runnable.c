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
struct TYPE_2__ {int /*<<< orphan*/  tk_work; } ;
struct rpc_task {int /*<<< orphan*/  tk_runstate; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_QUEUED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_async_schedule ; 
 int /*<<< orphan*/  rpc_clear_queued (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_test_and_set_running (struct rpc_task*) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpc_make_runnable(struct rpc_task *task)
{
	bool need_wakeup = !rpc_test_and_set_running(task);

	rpc_clear_queued(task);
	if (!need_wakeup)
		return;
	if (RPC_IS_ASYNC(task)) {
		INIT_WORK(&task->u.tk_work, rpc_async_schedule);
		queue_work(rpciod_workqueue, &task->u.tk_work);
	} else
		wake_up_bit(&task->tk_runstate, RPC_TASK_QUEUED);
}