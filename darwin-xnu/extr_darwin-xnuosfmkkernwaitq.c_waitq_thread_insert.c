#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct waitq {int /*<<< orphan*/  waitq_queue; int /*<<< orphan*/  waitq_prio_queue; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  wait_links; int /*<<< orphan*/  base_pri; int /*<<< orphan*/  wait_prioq_links; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE ; 
 int /*<<< orphan*/  THREAD_ADDED_TO_TURNSTILE_WAITQ ; 
 int /*<<< orphan*/  TSU_REGULAR_WAITQ_BLOCK_COUNT ; 
 int /*<<< orphan*/  TSU_TURNSTILE_BLOCK_COUNT ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  priority_queue_entry_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  priority_queue_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_stats_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ waitq_is_turnstile_queue (struct waitq*) ; 
 int /*<<< orphan*/  waitq_to_turnstile (struct waitq*) ; 

__attribute__((used)) static inline void waitq_thread_insert(struct waitq *wq,
                                       thread_t thread, boolean_t fifo)
{
	if (waitq_is_turnstile_queue(wq)) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (THREAD_ADDED_TO_TURNSTILE_WAITQ))) | DBG_FUNC_NONE,
			VM_KERNEL_UNSLIDE_OR_PERM(waitq_to_turnstile(wq)),
			thread_tid(thread),
			thread->base_pri, 0, 0);

		turnstile_stats_update(0, TSU_TURNSTILE_BLOCK_COUNT, NULL);

		/*
		 * For turnstile queues (which use priority queues), 
		 * insert the thread in the heap based on its current 
		 * base_pri. Note that the priority queue implementation 
		 * is currently not stable, so does not maintain fifo for 
		 * threads at the same base_pri. Also, if the base_pri 
		 * of the thread changes while its blocked in the waitq, 
		 * the thread position should be updated in the priority 
		 * queue by calling priority queue increase/decrease 
		 * operations.
		 */
		priority_queue_entry_init(&(thread->wait_prioq_links));
		priority_queue_insert(&wq->waitq_prio_queue,
				&thread->wait_prioq_links, thread->base_pri,
				PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE);
	} else {
		turnstile_stats_update(0, TSU_REGULAR_WAITQ_BLOCK_COUNT, NULL);
		if (fifo) {
			enqueue_tail(&wq->waitq_queue, &thread->wait_links);
		} else {
			enqueue_head(&wq->waitq_queue, &thread->wait_links);
		}
	}
}