#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* processor_t ;
struct TYPE_8__ {int /*<<< orphan*/  runq_bound_count; TYPE_1__* processor_set; } ;
struct TYPE_7__ {scalar_t__ bound_processor; } ;
struct TYPE_6__ {int /*<<< orphan*/  pset_runq_bound_count; } ;

/* Variables and functions */
 scalar_t__ PROCESSOR_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sched_traditional_use_pset_runqueue ; 

__attribute__((used)) __attribute__((always_inline))
static inline void runq_consider_decr_bound_count(processor_t processor,
						  thread_t thread)
{
	if (thread->bound_processor == PROCESSOR_NULL)
		return;

	assert(thread->bound_processor == processor);

	if (sched_traditional_use_pset_runqueue)
		processor->processor_set->pset_runq_bound_count--;

	processor->runq_bound_count--;
}