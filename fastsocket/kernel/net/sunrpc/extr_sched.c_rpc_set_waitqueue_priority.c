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
struct rpc_wait_queue {int priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_rotate_queue_owner (struct rpc_wait_queue*) ; 

__attribute__((used)) static void rpc_set_waitqueue_priority(struct rpc_wait_queue *queue, int priority)
{
	if (queue->priority != priority) {
		/* Fairness: rotate the list when changing priority */
		rpc_rotate_queue_owner(queue);
		queue->priority = priority;
	}
}