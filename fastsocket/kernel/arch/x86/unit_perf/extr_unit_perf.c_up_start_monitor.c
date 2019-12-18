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
struct cpu_cost_stats {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  UP_GET_CPU_CYCLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_up_monitor ; 
 struct cpu_cost_stats* get_monitorer_stats (struct unit_perf_monitor*,char const*) ; 
 struct unit_perf_monitor* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void up_start_monitor(const char *name)
{
	struct unit_perf_monitor *monitor;

	rcu_read_lock();
	monitor = rcu_dereference(g_up_monitor);
	if (monitor) {
		struct cpu_cost_stats *cost_stats = get_monitorer_stats(monitor, name);
		
		if (cost_stats) {
			UP_GET_CPU_CYCLES(cost_stats->start);
		}
	}
	rcu_read_unlock();
}