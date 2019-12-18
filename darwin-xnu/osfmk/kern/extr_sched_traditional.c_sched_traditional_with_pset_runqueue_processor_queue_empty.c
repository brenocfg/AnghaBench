#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_t ;
typedef  TYPE_2__* processor_set_t ;
typedef  int boolean_t ;
struct TYPE_8__ {int count; } ;
struct TYPE_7__ {scalar_t__ pset_runq_bound_count; } ;
struct TYPE_6__ {scalar_t__ runq_bound_count; TYPE_2__* processor_set; } ;

/* Variables and functions */
 TYPE_4__* runq_for_processor (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
sched_traditional_with_pset_runqueue_processor_queue_empty(processor_t processor)
{
	processor_set_t pset = processor->processor_set;
	int count = runq_for_processor(processor)->count;

	/*
	 * The pset runq contains the count of all runnable threads
	 * for all processors in the pset. However, for threads that
	 * are bound to another processor, the current "processor"
	 * is not eligible to execute the thread. So we only
	 * include bound threads that our bound to the current
	 * "processor". This allows the processor to idle when the
	 * count of eligible threads drops to 0, even if there's
	 * a runnable thread bound to a different processor in the
	 * shared runq.
	 */

	count -= pset->pset_runq_bound_count;
	count += processor->runq_bound_count;

	return count == 0;
}