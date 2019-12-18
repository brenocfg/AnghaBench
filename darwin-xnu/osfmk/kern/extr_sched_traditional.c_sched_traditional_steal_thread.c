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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  processor_t ;
typedef  TYPE_1__* processor_set_t ;
struct TYPE_9__ {scalar_t__ count; } ;
struct TYPE_8__ {int* cpu_state_map; } ;

/* Variables and functions */
 size_t PROCESSOR_DISPATCHING ; 
 size_t PROCESSOR_RUNNING ; 
 scalar_t__ THREAD_NULL ; 
 int lsb_first (int) ; 
 int lsb_next (int,int) ; 
 TYPE_1__* next_pset (TYPE_1__*) ; 
 int /*<<< orphan*/ * processor_array ; 
 int /*<<< orphan*/  pset_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  pset_unlock (TYPE_1__*) ; 
 TYPE_3__* runq_for_processor (int /*<<< orphan*/ ) ; 
 scalar_t__ sched_traditional_steal_processor_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static thread_t
sched_traditional_steal_thread(processor_set_t pset)
{
	processor_set_t nset, cset = pset;
	processor_t     processor;
	thread_t        thread;

	do {
		uint64_t active_map = (pset->cpu_state_map[PROCESSOR_RUNNING] |
				       pset->cpu_state_map[PROCESSOR_DISPATCHING]);
		for (int cpuid = lsb_first(active_map); cpuid >= 0; cpuid = lsb_next(active_map, cpuid)) {
			processor = processor_array[cpuid];
			if (runq_for_processor(processor)->count > 0) {
				thread = sched_traditional_steal_processor_thread(processor);
				if (thread != THREAD_NULL) {
					pset_unlock(cset);

					return (thread);
				}
			}
		}

		nset = next_pset(cset);

		if (nset != pset) {
			pset_unlock(cset);

			cset = nset;
			pset_lock(cset);
		}
	} while (nset != pset);

	pset_unlock(cset);

	return (THREAD_NULL);
}