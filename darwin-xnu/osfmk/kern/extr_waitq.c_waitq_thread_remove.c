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
struct waitq {int /*<<< orphan*/  waitq_prio_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  wait_links; int /*<<< orphan*/  wait_prioq_links; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE ; 
 int /*<<< orphan*/  THREAD_REMOVED_FROM_TURNSTILE_WAITQ ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priority_queue_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 
 scalar_t__ waitq_is_turnstile_queue (struct waitq*) ; 
 int /*<<< orphan*/  waitq_to_turnstile (struct waitq*) ; 

__attribute__((used)) static inline void waitq_thread_remove(struct waitq *wq,
                                       thread_t thread)
{
	if (waitq_is_turnstile_queue(wq)) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (THREAD_REMOVED_FROM_TURNSTILE_WAITQ))) | DBG_FUNC_NONE,
			VM_KERNEL_UNSLIDE_OR_PERM(waitq_to_turnstile(wq)),
			thread_tid(thread),
			0, 0, 0);
		priority_queue_remove(&wq->waitq_prio_queue, &thread->wait_prioq_links,
				PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE);
	} else {
		remqueue(&(thread->wait_links));
	}
}