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
struct priority_queue {int dummy; } ;
typedef  scalar_t__ priority_queue_key_t ;
typedef  int /*<<< orphan*/  priority_queue_entry_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE ; 
 scalar_t__ priority_queue_entry_decrease (struct priority_queue*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ priority_queue_entry_increase (struct priority_queue*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ priority_queue_entry_key (struct priority_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ priority_queue_max_key (struct priority_queue*) ; 

__attribute__((used)) static boolean_t
turnstile_priority_queue_update_entry_key(struct priority_queue *q,
		priority_queue_entry_t elt, priority_queue_key_t pri)
{
	priority_queue_key_t old_key = priority_queue_max_key(q);

	if (priority_queue_entry_key(q, elt) < pri) {
		if (priority_queue_entry_increase(q, elt, pri,
				PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE)) {
			return old_key != priority_queue_max_key(q);
		}
	} else if (priority_queue_entry_key(q, elt) > pri) {
		if (priority_queue_entry_decrease(q, elt, pri,
				PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE)) {
			return old_key != priority_queue_max_key(q);
		}
	}

	return FALSE;
}