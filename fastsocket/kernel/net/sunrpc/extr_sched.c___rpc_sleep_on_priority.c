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
struct rpc_task {int /*<<< orphan*/ * tk_callback; int /*<<< orphan*/  tk_client; int /*<<< orphan*/  tk_pid; } ;
typedef  int /*<<< orphan*/ * rpc_action ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rpc_add_timer (struct rpc_wait_queue*,struct rpc_task*) ; 
 int /*<<< orphan*/  __rpc_add_wait_queue (struct rpc_wait_queue*,struct rpc_task*,unsigned char) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rpc_qname (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  trace_rpc_task_sleep (int /*<<< orphan*/ ,struct rpc_task*,struct rpc_wait_queue*) ; 

__attribute__((used)) static void __rpc_sleep_on_priority(struct rpc_wait_queue *q,
		struct rpc_task *task,
		rpc_action action,
		unsigned char queue_priority)
{
	dprintk("RPC: %5u sleep_on(queue \"%s\" time %lu)\n",
			task->tk_pid, rpc_qname(q), jiffies);

	trace_rpc_task_sleep(task->tk_client, task, q);

	__rpc_add_wait_queue(q, task, queue_priority);

	BUG_ON(task->tk_callback != NULL);
	task->tk_callback = action;
	__rpc_add_timer(q, task);
}