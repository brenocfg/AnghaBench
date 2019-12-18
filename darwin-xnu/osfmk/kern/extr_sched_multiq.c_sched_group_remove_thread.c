#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* sched_group_t ;
typedef  int /*<<< orphan*/  sched_entry_t ;
typedef  int /*<<< orphan*/  integer_t ;
typedef  int /*<<< orphan*/  entry_queue_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  runq; } ;
struct TYPE_10__ {int /*<<< orphan*/  sched_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  entry_queue_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry_queue_remove_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_check_entry_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_check_run_queue (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  group_entry_for_pri (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ group_run_queue_remove_thread (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ multiq_sanity_check ; 
 int /*<<< orphan*/  sched_group_check_thread (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
sched_group_remove_thread(
                          entry_queue_t main_entryq,
                          sched_group_t group,
                          thread_t thread)
{
	integer_t thread_pri = thread->sched_pri;
	sched_entry_t sched_entry = group_entry_for_pri(group, thread_pri);

#if defined(MULTIQ_SANITY_CHECK)
	if (multiq_sanity_check) {
		global_check_entry_queue(main_entryq);
		group_check_run_queue(main_entryq, group);

		sched_group_check_thread(group, thread);
		entry_queue_check_entry(main_entryq, sched_entry, thread_pri);
	}
#endif

	boolean_t pri_level_empty = group_run_queue_remove_thread(&group->runq, thread, thread_pri);

	if (pri_level_empty) {
		entry_queue_remove_entry(main_entryq, sched_entry);
	}

#if defined(MULTIQ_SANITY_CHECK)
	if (multiq_sanity_check) {
		global_check_entry_queue(main_entryq);
		group_check_run_queue(main_entryq, group);
	}
#endif
}