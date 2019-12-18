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
struct unit_perf_monitor {int dummy; } ;
struct cpu_cost_stats {unsigned long long start; unsigned long long cost; int /*<<< orphan*/  overflow; int /*<<< orphan*/  call_times; } ;

/* Variables and functions */
 int /*<<< orphan*/  UP_GET_CPU_CYCLES (unsigned long long) ; 
 int /*<<< orphan*/  g_up_monitor ; 
 struct cpu_cost_stats* get_monitorer_stats (struct unit_perf_monitor*,char const*) ; 
 struct unit_perf_monitor* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void up_end_monitor(const char *name)
{
	struct unit_perf_monitor *monitor;
	unsigned long long end_time;

	UP_GET_CPU_CYCLES(end_time);	

	rcu_read_lock();
	monitor = rcu_dereference(g_up_monitor);
	if (monitor) {
		struct cpu_cost_stats *cost_stats = get_monitorer_stats(monitor, name);
		/* Check the cost_stats->start to avoid there is one new monitor during start and end */
		if (cost_stats && cost_stats->start) {
			unsigned long long old_cost = cost_stats->cost;
			unsigned long long cost = end_time-cost_stats->start;
		
			cost_stats->cost += cost;
			cost_stats->start = 0;
			cost_stats->call_times++;

			if (cost_stats->cost < old_cost) {
				//overflow happens
				cost_stats->overflow++;
			}
		}
	}
	rcu_read_unlock();
}