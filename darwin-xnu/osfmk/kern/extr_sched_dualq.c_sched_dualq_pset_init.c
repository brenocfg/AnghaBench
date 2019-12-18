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
struct TYPE_3__ {int /*<<< orphan*/  pset_runq; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_queue_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sched_dualq_pset_init(processor_set_t pset)
{
	run_queue_init(&pset->pset_runq);
}