#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  processor_t ;
typedef  int boolean_t ;
struct TYPE_2__ {int highq; } ;

/* Variables and functions */
 TYPE_1__* runq_for_processor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
sched_traditional_processor_queue_has_priority(processor_t      processor,
                                               int              priority,
                                               boolean_t        gte)
{
	if (gte)
		return runq_for_processor(processor)->highq >= priority;
	else
		return runq_for_processor(processor)->highq > priority;
}