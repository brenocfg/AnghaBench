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
struct rpc_task {int dummy; } ;

/* Variables and functions */
 struct rpc_task* __rpc_find_next_queued (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_wait_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_qname (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  rpc_wake_up_task_queue_locked (struct rpc_wait_queue*,struct rpc_task*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct rpc_task *rpc_wake_up_first(struct rpc_wait_queue *queue,
		bool (*func)(struct rpc_task *, void *), void *data)
{
	struct rpc_task	*task = NULL;

	dprintk("RPC:       wake_up_first(%p \"%s\")\n",
			queue, rpc_qname(queue));
	spin_lock_bh(&queue->lock);
	task = __rpc_find_next_queued(queue);
	if (task != NULL) {
		if (func(task, data))
			rpc_wake_up_task_queue_locked(queue, task);
		else
			task = NULL;
	}
	spin_unlock_bh(&queue->lock);

	return task;
}