#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  processor_t ;
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_3__ {scalar_t__ count; } ;

/* Variables and functions */
 TYPE_2__* dualq_bound_runq (int /*<<< orphan*/ ) ; 
 TYPE_1__* dualq_main_runq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
sched_dualq_processor_queue_empty(processor_t processor)
{
	return dualq_main_runq(processor)->count  == 0 &&
	       dualq_bound_runq(processor)->count == 0;
}