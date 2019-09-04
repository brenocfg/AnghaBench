#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* sched_entry_t ;
typedef  TYPE_3__* processor_t ;
typedef  int /*<<< orphan*/  processor_set_t ;
typedef  int /*<<< orphan*/  entry_queue_t ;
struct TYPE_10__ {int /*<<< orphan*/  current_pri; int /*<<< orphan*/  processor_set; } ;
struct TYPE_9__ {scalar_t__ runq; } ;
struct TYPE_8__ {int /*<<< orphan*/  sched_group; TYPE_3__* last_processor; } ;

/* Variables and functions */
 scalar_t__ MULTIQ_ERUNQ ; 
 int /*<<< orphan*/  SCHED_TAILQ ; 
 scalar_t__ deep_drain ; 
 int /*<<< orphan*/  entry_queue_change_entry (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* group_entry_for_pri (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiq_main_entryq (TYPE_3__*) ; 
 int /*<<< orphan*/  pset_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pset_unlock (int /*<<< orphan*/ ) ; 

void
sched_multiq_quantum_expire(thread_t thread)
{
	if (deep_drain) {
		/*
		 * Move the entry at this priority to the end of the queue,
		 * to allow the next task a shot at running.
		 */

		processor_t processor = thread->last_processor;
		processor_set_t pset = processor->processor_set;
		entry_queue_t entryq = multiq_main_entryq(processor);

		pset_lock(pset);

		sched_entry_t entry = group_entry_for_pri(thread->sched_group, processor->current_pri);

		if (entry->runq == MULTIQ_ERUNQ) {
			entry_queue_change_entry(entryq, entry, SCHED_TAILQ);
		}

		pset_unlock(pset);
	}
}