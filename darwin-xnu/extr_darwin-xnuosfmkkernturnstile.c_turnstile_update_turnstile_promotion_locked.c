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
struct turnstile {int ts_priority; int /*<<< orphan*/  ts_inheritor_links; int /*<<< orphan*/  ts_inheritor_queue; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  TURNSTILE_MOVED_IN_TURNSTILE_HEAP ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct turnstile*) ; 
 int priority_queue_entry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  turnstile_priority_queue_update_entry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  turnstile_recompute_priority_locked (struct turnstile*) ; 

__attribute__((used)) static boolean_t
turnstile_update_turnstile_promotion_locked(
	struct turnstile *dst_turnstile,
	struct turnstile *src_turnstile)
{
	int src_turnstile_link_priority;
	src_turnstile_link_priority = priority_queue_entry_key(&(dst_turnstile->ts_inheritor_queue),
				 &(src_turnstile->ts_inheritor_links));

	if (src_turnstile->ts_priority != src_turnstile_link_priority) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (TURNSTILE_MOVED_IN_TURNSTILE_HEAP))) | DBG_FUNC_NONE,
			VM_KERNEL_UNSLIDE_OR_PERM(dst_turnstile),
			VM_KERNEL_UNSLIDE_OR_PERM(src_turnstile),
			src_turnstile->ts_priority, src_turnstile_link_priority, 0);
	}

	if (!turnstile_priority_queue_update_entry_key(
			&dst_turnstile->ts_inheritor_queue, &src_turnstile->ts_inheritor_links,
			src_turnstile->ts_priority)) {
		return FALSE;
	}

	/* Update dst turnstile's priority */
	return turnstile_recompute_priority_locked(dst_turnstile);
}