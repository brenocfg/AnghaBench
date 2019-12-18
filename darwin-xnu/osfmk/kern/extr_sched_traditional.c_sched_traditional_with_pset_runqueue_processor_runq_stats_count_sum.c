#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
typedef  TYPE_3__* processor_t ;
struct TYPE_8__ {unsigned long long count_sum; } ;
struct TYPE_10__ {TYPE_2__ runq_stats; } ;
struct TYPE_9__ {scalar_t__ cpu_id; TYPE_1__* processor_set; } ;
struct TYPE_7__ {scalar_t__ cpu_set_low; } ;

/* Variables and functions */
 TYPE_5__* runq_for_processor (TYPE_3__*) ; 

__attribute__((used)) static uint64_t
sched_traditional_with_pset_runqueue_processor_runq_stats_count_sum(processor_t processor)
{
	if (processor->cpu_id == processor->processor_set->cpu_set_low)
		return runq_for_processor(processor)->runq_stats.count_sum;
	else
		return 0ULL;
}