#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_call_t ;
typedef  TYPE_2__* thread_call_group_t ;
typedef  int /*<<< orphan*/  queue_head_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  pending_count; int /*<<< orphan*/ * delayed_queues; int /*<<< orphan*/  pending_queue; } ;
struct TYPE_8__ {int tc_flags; int /*<<< orphan*/  tc_submit_count; scalar_t__ tc_deadline; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t TCF_ABSOLUTE ; 
 size_t TCF_CONTINUOUS ; 
 int THREAD_CALL_ONCE ; 
 int THREAD_CALL_RESCHEDULE ; 
 int THREAD_CALL_RUNNING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * call_entry_enqueue_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_wake (TYPE_2__*) ; 

__attribute__((used)) static __inline__ boolean_t
_pending_call_enqueue(thread_call_t             call,
                      thread_call_group_t       group)
{
	if ((THREAD_CALL_ONCE | THREAD_CALL_RUNNING)
	  == (call->tc_flags & (THREAD_CALL_ONCE | THREAD_CALL_RUNNING))) {
		call->tc_deadline = 0;

		uint32_t flags = call->tc_flags;
		call->tc_flags |= THREAD_CALL_RESCHEDULE;

		if ((flags & THREAD_CALL_RESCHEDULE) != 0)
			return (TRUE);
		else
			return (FALSE);
	}

	queue_head_t *old_queue = call_entry_enqueue_tail(CE(call), &group->pending_queue);

	if (old_queue == NULL) {
		call->tc_submit_count++;
	} else if (old_queue != &group->pending_queue &&
	           old_queue != &group->delayed_queues[TCF_ABSOLUTE] &&
	           old_queue != &group->delayed_queues[TCF_CONTINUOUS]) {
		panic("tried to move a thread call (%p) between groups (old_queue: %p)", call, old_queue);
	}

	group->pending_count++;

	thread_call_wake(group);

	return (old_queue != NULL);
}