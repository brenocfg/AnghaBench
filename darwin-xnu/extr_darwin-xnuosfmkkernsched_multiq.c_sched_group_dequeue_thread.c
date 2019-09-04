#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* sched_group_t ;
typedef  int /*<<< orphan*/  integer_t ;
typedef  int /*<<< orphan*/ * group_runq_t ;
typedef  int /*<<< orphan*/  entry_queue_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  runq; } ;
struct TYPE_7__ {int /*<<< orphan*/  runq; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PROCESSOR_NULL ; 
 int /*<<< orphan*/  entry_queue_remove_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_entry_for_pri (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* group_run_queue_dequeue_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static thread_t
sched_group_dequeue_thread(
                           entry_queue_t main_entryq,
                           sched_group_t group)
{
	group_runq_t group_runq = &group->runq;
	boolean_t pri_level_empty = FALSE;
	thread_t thread;
	integer_t thread_pri;

	thread = group_run_queue_dequeue_thread(group_runq, &thread_pri, &pri_level_empty);

	thread->runq = PROCESSOR_NULL;

	if (pri_level_empty) {
		entry_queue_remove_entry(main_entryq, group_entry_for_pri(group, thread_pri));
	}

	return thread;
}