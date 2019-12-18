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
typedef  int integer_t ;
typedef  int /*<<< orphan*/  entry_queue_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/ * entries; int /*<<< orphan*/  runq; } ;
struct TYPE_7__ {int sched_pri; } ;

/* Variables and functions */
 int SCHED_HEADQ ; 
 int /*<<< orphan*/  entry_queue_change_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  entry_queue_enqueue_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  global_check_entry_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_check_run_queue (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ group_run_queue_enqueue_thread (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 scalar_t__ multiq_sanity_check ; 

__attribute__((used)) static void
sched_group_enqueue_thread(
                           entry_queue_t        main_entryq,
                           sched_group_t        group,
                           thread_t             thread,
                           integer_t            options)
{
#if defined(MULTIQ_SANITY_CHECK)
	if (multiq_sanity_check) {
		global_check_entry_queue(main_entryq);
		group_check_run_queue(main_entryq, group);
	}
#endif

	int sched_pri = thread->sched_pri;

	boolean_t pri_level_was_empty = group_run_queue_enqueue_thread(&group->runq, thread, sched_pri, options);

	if (pri_level_was_empty) {
		/*
		 * TODO: Need to figure out if passing options here is a good idea or not
		 * What effects would it have?
		 */
		entry_queue_enqueue_entry(main_entryq, &group->entries[sched_pri], options);
	} else if (options & SCHED_HEADQ) {
		/* The thread should be at the head of the line - move its entry to the front */
		entry_queue_change_entry(main_entryq, &group->entries[sched_pri], options);
	}
}