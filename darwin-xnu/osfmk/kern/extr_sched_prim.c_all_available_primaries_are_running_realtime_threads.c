#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_1__* processor_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_6__ {int cpu_bitmask; int recommended_bitmask; } ;
struct TYPE_5__ {scalar_t__ state; scalar_t__ current_pri; struct TYPE_5__* processor_primary; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_RTQUEUES ; 
 scalar_t__ PROCESSOR_DISPATCHING ; 
 scalar_t__ PROCESSOR_IDLE ; 
 scalar_t__ PROCESSOR_RUNNING ; 
 int lsb_first (int) ; 
 int lsb_next (int,int) ; 
 TYPE_1__** processor_array ; 

__attribute__((used)) static bool
all_available_primaries_are_running_realtime_threads(processor_set_t pset)
{
	uint64_t cpu_map = (pset->cpu_bitmask & pset->recommended_bitmask);

	for (int cpuid = lsb_first(cpu_map); cpuid >= 0; cpuid = lsb_next(cpu_map, cpuid)) {
		processor_t processor = processor_array[cpuid];

		if (processor->processor_primary != processor) {
			continue;
		}

		if (processor->state == PROCESSOR_IDLE) {
			return false;
		}

		if (processor->state == PROCESSOR_DISPATCHING) {
			return false;
		}

		if (processor->state != PROCESSOR_RUNNING) {
			/*
			 * All other processor states are considered unavailable to run
			 * realtime threads.  In particular, we prefer an available secondary
			 * processor over the risk of leaving a realtime thread on the run queue
			 * while waiting for a processor in PROCESSOR_START state,
			 * which should anyway be a rare case.
			 */
			continue;
		}

		if (processor->current_pri < BASEPRI_RTQUEUES) {
			return false;
		}
	}

	return true;
}