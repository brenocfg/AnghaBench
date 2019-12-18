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
struct cpufreq_stats {int state_num; int* freq_table; int /*<<< orphan*/ * time_in_state; int /*<<< orphan*/  cpu; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_stats_table ; 
 int /*<<< orphan*/  cpufreq_stats_update (int /*<<< orphan*/ ) ; 
 scalar_t__ cputime64_to_clock_t (int /*<<< orphan*/ ) ; 
 struct cpufreq_stats* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int,unsigned long long) ; 

__attribute__((used)) static ssize_t show_time_in_state(struct cpufreq_policy *policy, char *buf)
{
	ssize_t len = 0;
	int i;
	struct cpufreq_stats *stat = per_cpu(cpufreq_stats_table, policy->cpu);
	if (!stat)
		return 0;
	cpufreq_stats_update(stat->cpu);
	for (i = 0; i < stat->state_num; i++) {
		len += sprintf(buf + len, "%u %llu\n", stat->freq_table[i],
			(unsigned long long)
			cputime64_to_clock_t(stat->time_in_state[i]));
	}
	return len;
}