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
struct rpc_wait_queue {int /*<<< orphan*/  lock; } ;
struct rpc_task {void (* tk_callback ) (struct rpc_task*) ;void (* tk_action ) (struct rpc_task*) ;int /*<<< orphan*/  tk_status; int /*<<< orphan*/  tk_pid; int /*<<< orphan*/  tk_flags; int /*<<< orphan*/  tk_runstate; struct rpc_wait_queue* tk_waitqueue; int /*<<< orphan*/  tk_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ERESTARTSYS ; 
 int RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_IS_QUEUED (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_KILLED ; 
 int /*<<< orphan*/  RPC_TASK_QUEUED ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,...) ; 
 int out_of_line_wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_clear_running (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int) ; 
 int /*<<< orphan*/  rpc_release_task (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_set_running (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_wait_bit_killable ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rpc_task_run_action (int /*<<< orphan*/ ,struct rpc_task*,void (*) (struct rpc_task*)) ; 

__attribute__((used)) static void __rpc_execute(struct rpc_task *task)
{
	struct rpc_wait_queue *queue;
	int task_is_async = RPC_IS_ASYNC(task);
	int status = 0;

	dprintk("RPC: %5u __rpc_execute flags=0x%x\n",
			task->tk_pid, task->tk_flags);

	BUG_ON(RPC_IS_QUEUED(task));

	for (;;) {
		void (*do_action)(struct rpc_task *);

		/*
		 * Execute any pending callback first.
		 */
		do_action = task->tk_callback;
		task->tk_callback = NULL;
		if (do_action == NULL) {
			/*
			 * Perform the next FSM step.
			 * tk_action may be NULL if the task has been killed.
			 * In particular, note that rpc_killall_tasks may
			 * do this at any time, so beware when dereferencing.
			 */
			do_action = task->tk_action;
			if (do_action == NULL)
				break;
		}
		trace_rpc_task_run_action(task->tk_client, task, task->tk_action);
		do_action(task);

		/*
		 * Lockless check for whether task is sleeping or not.
		 */
		if (!RPC_IS_QUEUED(task))
			continue;
		/*
		 * The queue->lock protects against races with
		 * rpc_make_runnable().
		 *
		 * Note that once we clear RPC_TASK_RUNNING on an asynchronous
		 * rpc_task, rpc_make_runnable() can assign it to a
		 * different workqueue. We therefore cannot assume that the
		 * rpc_task pointer may still be dereferenced.
		 */
		queue = task->tk_waitqueue;
		spin_lock_bh(&queue->lock);
		if (!RPC_IS_QUEUED(task)) {
			spin_unlock_bh(&queue->lock);
			continue;
		}
		rpc_clear_running(task);
		spin_unlock_bh(&queue->lock);
		if (task_is_async)
			return;

		/* sync task: sleep here */
		dprintk("RPC: %5u sync task going to sleep\n", task->tk_pid);
		status = out_of_line_wait_on_bit(&task->tk_runstate,
				RPC_TASK_QUEUED, rpc_wait_bit_killable,
				TASK_KILLABLE);
		if (status == -ERESTARTSYS) {
			/*
			 * When a sync task receives a signal, it exits with
			 * -ERESTARTSYS. In order to catch any callbacks that
			 * clean up after sleeping on some queue, we don't
			 * break the loop here, but go around once more.
			 */
			dprintk("RPC: %5u got signal\n", task->tk_pid);
			task->tk_flags |= RPC_TASK_KILLED;
			rpc_exit(task, -ERESTARTSYS);
		}
		rpc_set_running(task);
		dprintk("RPC: %5u sync task resuming\n", task->tk_pid);
	}

	dprintk("RPC: %5u return %d, status %d\n", task->tk_pid, status,
			task->tk_status);
	/* Release all resources associated with the task */
	rpc_release_task(task);
}