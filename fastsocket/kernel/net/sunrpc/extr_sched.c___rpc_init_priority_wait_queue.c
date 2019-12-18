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
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  timer; } ;
struct rpc_wait_queue {unsigned char maxpriority; char const* name; TYPE_1__ timer_list; scalar_t__ qlen; int /*<<< orphan*/ * tasks; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __rpc_queue_timer_fn ; 
 int /*<<< orphan*/  rpc_reset_waitqueue_priority (struct rpc_wait_queue*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rpc_init_priority_wait_queue(struct rpc_wait_queue *queue, const char *qname, unsigned char nr_queues)
{
	int i;

	spin_lock_init(&queue->lock);
	for (i = 0; i < ARRAY_SIZE(queue->tasks); i++)
		INIT_LIST_HEAD(&queue->tasks[i]);
	queue->maxpriority = nr_queues - 1;
	rpc_reset_waitqueue_priority(queue);
	queue->qlen = 0;
	setup_timer(&queue->timer_list.timer, __rpc_queue_timer_fn, (unsigned long)queue);
	INIT_LIST_HEAD(&queue->timer_list.list);
#ifdef RPC_DEBUG
	queue->name = qname;
#endif
}