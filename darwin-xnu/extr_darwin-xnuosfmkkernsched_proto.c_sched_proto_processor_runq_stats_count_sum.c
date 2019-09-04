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
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ processor_t ;
struct TYPE_3__ {unsigned long long count_sum; } ;
struct TYPE_4__ {TYPE_1__ runq_stats; } ;

/* Variables and functions */
 TYPE_2__* global_runq ; 
 scalar_t__ master_processor ; 

__attribute__((used)) static uint64_t
sched_proto_processor_runq_stats_count_sum(processor_t   processor)
{
	if (master_processor == processor) {
		return global_runq->runq_stats.count_sum;
	} else {
		return 0ULL;
	}
}