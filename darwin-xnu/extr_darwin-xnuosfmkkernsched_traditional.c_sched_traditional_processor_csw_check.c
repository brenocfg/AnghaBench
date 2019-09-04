#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* run_queue_t ;
typedef  TYPE_2__* processor_t ;
typedef  int boolean_t ;
typedef  int ast_t ;
struct TYPE_7__ {scalar_t__ current_pri; scalar_t__ first_timeslice; int /*<<< orphan*/ * active_thread; } ;
struct TYPE_6__ {scalar_t__ highq; scalar_t__ urgency; } ;

/* Variables and functions */
 int AST_NONE ; 
 int AST_PREEMPT ; 
 int AST_URGENT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* runq_for_processor (TYPE_2__*) ; 

__attribute__((used)) static ast_t
sched_traditional_processor_csw_check(processor_t processor)
{
	run_queue_t     runq;
	boolean_t       has_higher;

	assert(processor->active_thread != NULL);

	runq = runq_for_processor(processor);

	if (processor->first_timeslice) {
		has_higher = (runq->highq > processor->current_pri);
	} else {
		has_higher = (runq->highq >= processor->current_pri);
	}

	if (has_higher) {
		if (runq->urgency > 0)
			return (AST_PREEMPT | AST_URGENT);

		return AST_PREEMPT;
	}

	return AST_NONE;
}