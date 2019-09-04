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
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* processor_t ;
struct TYPE_6__ {scalar_t__ current_pri; struct TYPE_6__* processor_primary; } ;
struct TYPE_5__ {scalar_t__ sched_pri; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_RTQUEUES ; 
 int /*<<< orphan*/  sched_allow_rt_smt ; 

__attribute__((used)) static bool
sched_multiq_thread_avoid_processor(processor_t processor, thread_t thread)
{
	if (processor->processor_primary != processor) {
		/*
		 * This is a secondary SMT processor.  If the primary is running
		 * a realtime thread, only allow realtime threads on the secondary.
		 */
		if ((processor->processor_primary->current_pri >= BASEPRI_RTQUEUES) && ((thread->sched_pri < BASEPRI_RTQUEUES) || !sched_allow_rt_smt)) {
			return true;
		}
	}

	return false;
}