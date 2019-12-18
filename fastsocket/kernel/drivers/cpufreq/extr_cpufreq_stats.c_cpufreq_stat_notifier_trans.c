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
struct notifier_block {int dummy; } ;
struct cpufreq_stats {int last_index; int max_state; int /*<<< orphan*/  total_trans; int /*<<< orphan*/ * trans_table; } ;
struct cpufreq_freqs {int /*<<< orphan*/  cpu; int /*<<< orphan*/  new; } ;

/* Variables and functions */
 unsigned long CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  cpufreq_stats_lock ; 
 int /*<<< orphan*/  cpufreq_stats_table ; 
 int /*<<< orphan*/  cpufreq_stats_update (int /*<<< orphan*/ ) ; 
 int freq_table_get_index (struct cpufreq_stats*,int /*<<< orphan*/ ) ; 
 struct cpufreq_stats* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpufreq_stat_notifier_trans(struct notifier_block *nb,
		unsigned long val, void *data)
{
	struct cpufreq_freqs *freq = data;
	struct cpufreq_stats *stat;
	int old_index, new_index;

	if (val != CPUFREQ_POSTCHANGE)
		return 0;

	stat = per_cpu(cpufreq_stats_table, freq->cpu);
	if (!stat)
		return 0;

	old_index = stat->last_index;
	new_index = freq_table_get_index(stat, freq->new);

	cpufreq_stats_update(freq->cpu);
	if (old_index == new_index)
		return 0;

	if (old_index == -1 || new_index == -1)
		return 0;

	spin_lock(&cpufreq_stats_lock);
	stat->last_index = new_index;
#ifdef CONFIG_CPU_FREQ_STAT_DETAILS
	stat->trans_table[old_index * stat->max_state + new_index]++;
#endif
	stat->total_trans++;
	spin_unlock(&cpufreq_stats_lock);
	return 0;
}