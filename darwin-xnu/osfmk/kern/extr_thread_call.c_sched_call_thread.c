#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* thread_call_group_t ;
struct TYPE_9__ {int active_count; int blocked_count; int /*<<< orphan*/  pending_count; } ;
struct TYPE_7__ {TYPE_3__* thc_group; } ;
struct TYPE_8__ {TYPE_1__ thc_state; } ;

/* Variables and functions */
#define  SCHED_CALL_BLOCK 129 
#define  SCHED_CALL_UNBLOCK 128 
 int THREAD_CALL_INDEX_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* thread_call_groups ; 
 int /*<<< orphan*/  thread_call_lock_spin () ; 
 int /*<<< orphan*/  thread_call_unlock () ; 
 int /*<<< orphan*/  thread_call_wake (TYPE_3__*) ; 

__attribute__((used)) static void
sched_call_thread(
		int				type,
		thread_t		thread)
{
	thread_call_group_t		group;

	group = thread->thc_state.thc_group;
	assert((group - &thread_call_groups[0]) < THREAD_CALL_INDEX_MAX);

	thread_call_lock_spin();

	switch (type) {

		case SCHED_CALL_BLOCK:
			assert(group->active_count);
			--group->active_count;
			group->blocked_count++;
			if (group->pending_count > 0)
				thread_call_wake(group);
			break;

		case SCHED_CALL_UNBLOCK:
			assert(group->blocked_count);
			--group->blocked_count;
			group->active_count++;
			break;
	}

	thread_call_unlock();
}