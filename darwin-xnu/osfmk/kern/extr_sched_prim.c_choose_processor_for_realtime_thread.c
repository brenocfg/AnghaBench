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
typedef  int uint64_t ;
typedef  TYPE_1__* processor_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_8__ {int cpu_bitmask; int recommended_bitmask; int pending_AST_cpu_mask; } ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ current_pri; struct TYPE_7__* processor_primary; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_RTQUEUES ; 
 scalar_t__ PROCESSOR_DISPATCHING ; 
 scalar_t__ PROCESSOR_IDLE ; 
 TYPE_1__* PROCESSOR_NULL ; 
 scalar_t__ PROCESSOR_RUNNING ; 
 int lsb_first (int) ; 
 int lsb_next (int,int) ; 
 TYPE_1__** processor_array ; 
 int /*<<< orphan*/  sched_allow_rt_smt ; 

__attribute__((used)) static processor_t
choose_processor_for_realtime_thread(processor_set_t pset)
{
	uint64_t cpu_map = (pset->cpu_bitmask & pset->recommended_bitmask & ~pset->pending_AST_cpu_mask);

	for (int cpuid = lsb_first(cpu_map); cpuid >= 0; cpuid = lsb_next(cpu_map, cpuid)) {
		processor_t processor = processor_array[cpuid];

		if (processor->processor_primary != processor) {
			continue;
		}

		if (processor->state == PROCESSOR_IDLE) {
			return processor;
		}

		if ((processor->state != PROCESSOR_RUNNING) && (processor->state != PROCESSOR_DISPATCHING)) {
			continue;
		}

		if (processor->current_pri >= BASEPRI_RTQUEUES) {
			continue;
		}

		return processor;

	}

	if (!sched_allow_rt_smt) {
		return PROCESSOR_NULL;
	}

	/* Consider secondary processors */
	for (int cpuid = lsb_first(cpu_map); cpuid >= 0; cpuid = lsb_next(cpu_map, cpuid)) {
		processor_t processor = processor_array[cpuid];

		if (processor->processor_primary == processor) {
			continue;
		}

		if (processor->state == PROCESSOR_IDLE) {
			return processor;
		}

		if ((processor->state != PROCESSOR_RUNNING) && (processor->state != PROCESSOR_DISPATCHING)) {
			continue;
		}

		if (processor->current_pri >= BASEPRI_RTQUEUES) {
			continue;
		}

		return processor;

	}

	return PROCESSOR_NULL;
}