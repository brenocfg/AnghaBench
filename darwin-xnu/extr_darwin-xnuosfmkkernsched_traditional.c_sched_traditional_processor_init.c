#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_t ;
struct TYPE_3__ {scalar_t__ runq_bound_count; int /*<<< orphan*/  runq; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_traditional_use_pset_runqueue ; 

__attribute__((used)) static void
sched_traditional_processor_init(processor_t processor)
{
	if (!sched_traditional_use_pset_runqueue) {
		run_queue_init(&processor->runq);
	}
	processor->runq_bound_count = 0;
}