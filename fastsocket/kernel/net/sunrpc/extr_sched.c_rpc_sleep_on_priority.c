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
typedef  int /*<<< orphan*/  rpc_action ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RPC_IS_ACTIVATED (struct rpc_task*) ; 
 scalar_t__ RPC_PRIORITY_LOW ; 
 int /*<<< orphan*/  __rpc_sleep_on_priority (struct rpc_wait_queue*,struct rpc_task*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rpc_sleep_on_priority(struct rpc_wait_queue *q, struct rpc_task *task,
		rpc_action action, int priority)
{
	/* We shouldn't ever put an inactive task to sleep */
	BUG_ON(!RPC_IS_ACTIVATED(task));

	/*
	 * Protect the queue operations.
	 */
	spin_lock_bh(&q->lock);
	__rpc_sleep_on_priority(q, task, action, priority - RPC_PRIORITY_LOW);
	spin_unlock_bh(&q->lock);
}