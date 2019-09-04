#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  waitq_prio_queue; } ;
struct turnstile {TYPE_1__ ts_waitq; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int base_pri; int /*<<< orphan*/  wait_prioq_links; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_MOVED_IN_TURNSTILE_WAITQ ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct turnstile*) ; 
 int priority_queue_entry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_tid (TYPE_2__*) ; 
 int /*<<< orphan*/  turnstile_priority_queue_update_entry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  turnstile_recompute_priority_locked (struct turnstile*) ; 

__attribute__((used)) static boolean_t
turnstile_update_thread_promotion_locked(
	struct turnstile *dst_turnstile,
	thread_t thread)
{
	int thread_link_priority = priority_queue_entry_key(&(dst_turnstile->ts_waitq.waitq_prio_queue),
				 &(thread->wait_prioq_links));

	if (thread->base_pri != thread_link_priority) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (THREAD_MOVED_IN_TURNSTILE_WAITQ))) | DBG_FUNC_NONE,
			VM_KERNEL_UNSLIDE_OR_PERM(dst_turnstile),
			thread_tid(thread),
			thread->base_pri,
			thread_link_priority, 0);
	}

	if (!turnstile_priority_queue_update_entry_key(
			&dst_turnstile->ts_waitq.waitq_prio_queue,
			&thread->wait_prioq_links, thread->base_pri)) {
		return FALSE;
	}

	/* Update dst turnstile's priority */
	return turnstile_recompute_priority_locked(dst_turnstile);
}