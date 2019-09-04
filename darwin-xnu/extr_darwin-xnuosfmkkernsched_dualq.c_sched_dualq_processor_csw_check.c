#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* run_queue_t ;
typedef  TYPE_2__* processor_t ;
typedef  int boolean_t ;
typedef  int ast_t ;
struct TYPE_10__ {int current_pri; scalar_t__ first_timeslice; int /*<<< orphan*/ * active_thread; } ;
struct TYPE_9__ {scalar_t__ urgency; int /*<<< orphan*/  highq; } ;

/* Variables and functions */
 int AST_NONE ; 
 int AST_PREEMPT ; 
 int AST_URGENT ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_1__* dualq_bound_runq (TYPE_2__*) ; 
 TYPE_1__* dualq_main_runq (TYPE_2__*) ; 
 scalar_t__ sched_dualq_thread_avoid_processor (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ast_t
sched_dualq_processor_csw_check(processor_t processor)
{
	boolean_t       has_higher;
	int             pri;

	if (sched_dualq_thread_avoid_processor(processor, current_thread())) {
		return (AST_PREEMPT | AST_URGENT);
	}

	run_queue_t main_runq  = dualq_main_runq(processor);
	run_queue_t bound_runq = dualq_bound_runq(processor);

	assert(processor->active_thread != NULL);

	pri = MAX(main_runq->highq, bound_runq->highq);

	if (processor->first_timeslice) {
		has_higher = (pri > processor->current_pri);
	} else {
		has_higher = (pri >= processor->current_pri);
	}

	if (has_higher) {
		if (main_runq->urgency > 0)
			return (AST_PREEMPT | AST_URGENT);

		if (bound_runq->urgency > 0)
			return (AST_PREEMPT | AST_URGENT);
		
		return AST_PREEMPT;
	}

	return AST_NONE;
}