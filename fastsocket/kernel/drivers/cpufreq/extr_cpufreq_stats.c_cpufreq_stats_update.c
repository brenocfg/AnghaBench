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
struct cpufreq_stats {size_t last_index; unsigned long long last_time; int /*<<< orphan*/ * time_in_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_stats_lock ; 
 int /*<<< orphan*/  cpufreq_stats_table ; 
 int /*<<< orphan*/  cputime64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_sub (unsigned long long,unsigned long long) ; 
 unsigned long long get_jiffies_64 () ; 
 struct cpufreq_stats* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpufreq_stats_update(unsigned int cpu)
{
	struct cpufreq_stats *stat;
	unsigned long long cur_time;

	cur_time = get_jiffies_64();
	spin_lock(&cpufreq_stats_lock);
	stat = per_cpu(cpufreq_stats_table, cpu);
	if (stat->time_in_state)
		stat->time_in_state[stat->last_index] =
			cputime64_add(stat->time_in_state[stat->last_index],
				      cputime_sub(cur_time, stat->last_time));
	stat->last_time = cur_time;
	spin_unlock(&cpufreq_stats_lock);
	return 0;
}