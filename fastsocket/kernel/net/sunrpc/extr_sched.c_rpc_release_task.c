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
struct rpc_task {int /*<<< orphan*/  tk_workqueue; int /*<<< orphan*/  tk_count; int /*<<< orphan*/  tk_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_IS_QUEUED (struct rpc_task*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_complete_task (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_final_put_task (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_release_resources_task (struct rpc_task*) ; 

__attribute__((used)) static void rpc_release_task(struct rpc_task *task)
{
	dprintk("RPC: %5u release task\n", task->tk_pid);

	BUG_ON (RPC_IS_QUEUED(task));

	rpc_release_resources_task(task);

	/*
	 * Note: at this point we have been removed from rpc_clnt->cl_tasks,
	 * so it should be safe to use task->tk_count as a test for whether
	 * or not any other processes still hold references to our rpc_task.
	 */
	if (atomic_read(&task->tk_count) != 1 + !RPC_IS_ASYNC(task)) {
		/* Wake up anyone who may be waiting for task completion */
		if (!rpc_complete_task(task))
			return;
	} else {
		if (!atomic_dec_and_test(&task->tk_count))
			return;
	}
	rpc_final_put_task(task, task->tk_workqueue);
}