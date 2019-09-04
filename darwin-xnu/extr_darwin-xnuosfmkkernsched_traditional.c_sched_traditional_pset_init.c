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
typedef  TYPE_1__* processor_set_t ;
struct TYPE_3__ {scalar_t__ pset_runq_bound_count; int /*<<< orphan*/  pset_runq; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_queue_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sched_traditional_use_pset_runqueue ; 

__attribute__((used)) static void
sched_traditional_pset_init(processor_set_t pset)
{
	if (sched_traditional_use_pset_runqueue) {
		run_queue_init(&pset->pset_runq);
	}
	pset->pset_runq_bound_count = 0;
}