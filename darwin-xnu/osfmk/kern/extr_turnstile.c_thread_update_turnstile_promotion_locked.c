#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct turnstile {int ts_priority; int /*<<< orphan*/  ts_inheritor_links; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  inheritor_queue; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  TURNSTILE_MOVED_IN_THREAD_HEAP ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct turnstile*) ; 
 int priority_queue_entry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_recompute_user_promotion_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_priority_queue_update_entry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static boolean_t
thread_update_turnstile_promotion_locked(
	thread_t thread,
	struct turnstile *turnstile)
{
	int turnstile_link_priority = priority_queue_entry_key(&(thread->inheritor_queue),
				 &(turnstile->ts_inheritor_links));

	if (turnstile->ts_priority != turnstile_link_priority) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (TURNSTILE_MOVED_IN_THREAD_HEAP))) | DBG_FUNC_NONE,
			thread_tid(thread),
			VM_KERNEL_UNSLIDE_OR_PERM(turnstile),
			turnstile->ts_priority,
			turnstile_link_priority, 0);
	}

	if (!turnstile_priority_queue_update_entry_key(&thread->inheritor_queue,
			&turnstile->ts_inheritor_links, turnstile->ts_priority)) {
		return FALSE;
	}

	/* Update thread priority */
	return thread_recompute_user_promotion_locked(thread);
}