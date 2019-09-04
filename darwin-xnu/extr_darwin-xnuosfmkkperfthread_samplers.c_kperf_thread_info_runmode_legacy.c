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
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* processor_t ;
struct TYPE_6__ {TYPE_1__* active_thread; } ;
struct TYPE_5__ {int state; TYPE_2__* last_processor; } ;

/* Variables and functions */
 int KPERF_TI_IDLE ; 
 int KPERF_TI_RUNNABLE ; 
 int KPERF_TI_RUNNING ; 
 int KPERF_TI_SUSP ; 
 int KPERF_TI_TERMINATE ; 
 int KPERF_TI_UNINT ; 
 int KPERF_TI_WAIT ; 
 TYPE_2__* PROCESSOR_NULL ; 
 int TH_IDLE ; 
 int TH_RUN ; 
 int TH_SUSP ; 
 int TH_TERMINATE ; 
 int TH_UNINT ; 
 int TH_WAIT ; 

__attribute__((used)) static uint32_t
kperf_thread_info_runmode_legacy(thread_t thread)
{
	uint32_t kperf_state = 0;
	int sched_state = thread->state;
	processor_t last_processor = thread->last_processor;

	if ((last_processor != PROCESSOR_NULL) && (thread == last_processor->active_thread)) {
		kperf_state |= KPERF_TI_RUNNING;
	}
	if (sched_state & TH_RUN) {
		kperf_state |= KPERF_TI_RUNNABLE;
	}
	if (sched_state & TH_WAIT) {
		kperf_state |= KPERF_TI_WAIT;
	}
	if (sched_state & TH_UNINT) {
		kperf_state |= KPERF_TI_UNINT;
	}
	if (sched_state & TH_SUSP) {
		kperf_state |= KPERF_TI_SUSP;
	}
	if (sched_state & TH_TERMINATE) {
		kperf_state |= KPERF_TI_TERMINATE;
	}
	if (sched_state & TH_IDLE) {
		kperf_state |= KPERF_TI_IDLE;
	}

#if !CONFIG_EMBEDDED
	/* on desktop, if state is blank, leave not idle set */
	if (kperf_state == 0) {
		return (TH_IDLE << 16);
	}
#endif /* !CONFIG_EMBEDDED */

	/* high two bytes are inverted mask, low two bytes are normal */
	return (((~kperf_state & 0xffff) << 16) | (kperf_state & 0xffff));
}