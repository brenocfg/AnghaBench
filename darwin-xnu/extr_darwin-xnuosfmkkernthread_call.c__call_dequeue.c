#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_call_t ;
typedef  TYPE_2__* thread_call_group_t ;
typedef  int /*<<< orphan*/  queue_head_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  pending_count; int /*<<< orphan*/  pending_queue; int /*<<< orphan*/ * delayed_queues; } ;
struct TYPE_6__ {int /*<<< orphan*/  tc_finish_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE (TYPE_1__*) ; 
 size_t TCF_ABSOLUTE ; 
 size_t TCF_CONTINUOUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * call_entry_dequeue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ boolean_t
_call_dequeue(
	thread_call_t		call,
	thread_call_group_t	group)
{
	queue_head_t		*old_queue;

	old_queue = call_entry_dequeue(CE(call));

	if (old_queue != NULL) {
		assert(old_queue == &group->pending_queue ||
		       old_queue == &group->delayed_queues[TCF_ABSOLUTE] ||
		       old_queue == &group->delayed_queues[TCF_CONTINUOUS]);

		call->tc_finish_count++;
		if (old_queue == &group->pending_queue)
			group->pending_count--;
	}

	return (old_queue != NULL);
}