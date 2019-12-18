#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARDWARE ; 
 int /*<<< orphan*/  HW_BRANCH_INSTRUCTIONS ; 
 int /*<<< orphan*/  HW_CACHE ; 
 int /*<<< orphan*/  HW_CACHE_DTLB ; 
 int /*<<< orphan*/  HW_CACHE_ITLB ; 
 int /*<<< orphan*/  HW_CACHE_L1D ; 
 int /*<<< orphan*/  HW_CACHE_L1I ; 
 int /*<<< orphan*/  HW_CACHE_LL ; 
 int /*<<< orphan*/  HW_CACHE_REFERENCES ; 
 int /*<<< orphan*/  HW_CPU_CYCLES ; 
 int /*<<< orphan*/  HW_STALLED_CYCLES_BACKEND ; 
 int /*<<< orphan*/  HW_STALLED_CYCLES_FRONTEND ; 
 int /*<<< orphan*/  SOFTWARE ; 
 int /*<<< orphan*/  SW_TASK_CLOCK ; 
 scalar_t__ perf_evsel__match (struct perf_evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * runtime_branches_stats ; 
 int /*<<< orphan*/ * runtime_cacherefs_stats ; 
 int /*<<< orphan*/ * runtime_cycles_stats ; 
 int /*<<< orphan*/ * runtime_dtlb_cache_stats ; 
 int /*<<< orphan*/ * runtime_itlb_cache_stats ; 
 int /*<<< orphan*/ * runtime_l1_dcache_stats ; 
 int /*<<< orphan*/ * runtime_l1_icache_stats ; 
 int /*<<< orphan*/ * runtime_ll_cache_stats ; 
 int /*<<< orphan*/ * runtime_nsecs_stats ; 
 int /*<<< orphan*/ * runtime_stalled_cycles_back_stats ; 
 int /*<<< orphan*/ * runtime_stalled_cycles_front_stats ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_shadow_stats(struct perf_evsel *counter, u64 *count)
{
	if (perf_evsel__match(counter, SOFTWARE, SW_TASK_CLOCK))
		update_stats(&runtime_nsecs_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_CPU_CYCLES))
		update_stats(&runtime_cycles_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_FRONTEND))
		update_stats(&runtime_stalled_cycles_front_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_BACKEND))
		update_stats(&runtime_stalled_cycles_back_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_BRANCH_INSTRUCTIONS))
		update_stats(&runtime_branches_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_CACHE_REFERENCES))
		update_stats(&runtime_cacherefs_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_L1D))
		update_stats(&runtime_l1_dcache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_L1I))
		update_stats(&runtime_l1_icache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_LL))
		update_stats(&runtime_ll_cache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_DTLB))
		update_stats(&runtime_dtlb_cache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_ITLB))
		update_stats(&runtime_itlb_cache_stats[0], count[0]);
}