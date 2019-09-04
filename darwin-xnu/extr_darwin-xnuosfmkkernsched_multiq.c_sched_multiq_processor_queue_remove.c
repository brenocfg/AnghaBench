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
typedef  TYPE_2__* processor_t ;
typedef  int /*<<< orphan*/  processor_set_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  processor_set; } ;
struct TYPE_10__ {int /*<<< orphan*/  sched_group; TYPE_2__* runq; TYPE_2__* bound_processor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* PROCESSOR_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  multiq_bound_runq (TYPE_2__*) ; 
 int /*<<< orphan*/  multiq_main_entryq (TYPE_2__*) ; 
 int /*<<< orphan*/  pset_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pset_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_queue_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sched_group_remove_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static boolean_t
sched_multiq_processor_queue_remove(
                                    processor_t processor,
                                    thread_t    thread)
{
	boolean_t removed = FALSE;
	processor_set_t pset = processor->processor_set;

	pset_lock(pset);

	if (thread->runq != PROCESSOR_NULL) {
		/*
		 * Thread is on a run queue and we have a lock on
		 * that run queue.
		 */

		assert(thread->runq == processor);

		if (thread->bound_processor != PROCESSOR_NULL) {
			assert(processor == thread->bound_processor);
			run_queue_remove(multiq_bound_runq(processor), thread);
			thread->runq = PROCESSOR_NULL;
		} else {
			sched_group_remove_thread(multiq_main_entryq(processor),
			                          thread->sched_group,
			                          thread);
		}

		removed = TRUE;
	}

	pset_unlock(pset);

	return removed;
}