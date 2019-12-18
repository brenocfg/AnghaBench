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
struct pxa3xx_freq_info {int cpufreq_mhz; } ;
struct cpufreq_policy {int dummy; } ;
struct cpufreq_frequency_table {int index; int frequency; } ;

/* Variables and functions */
 int CPUFREQ_TABLE_END ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,struct cpufreq_frequency_table*) ; 
 struct cpufreq_frequency_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pxa3xx_freq_info* pxa3xx_freqs ; 
 int pxa3xx_freqs_num ; 
 struct cpufreq_frequency_table* pxa3xx_freqs_table ; 

__attribute__((used)) static int setup_freqs_table(struct cpufreq_policy *policy,
			     struct pxa3xx_freq_info *freqs, int num)
{
	struct cpufreq_frequency_table *table;
	int i;

	table = kzalloc((num + 1) * sizeof(*table), GFP_KERNEL);
	if (table == NULL)
		return -ENOMEM;

	for (i = 0; i < num; i++) {
		table[i].index = i;
		table[i].frequency = freqs[i].cpufreq_mhz * 1000;
	}
	table[num].index = i;
	table[num].frequency = CPUFREQ_TABLE_END;

	pxa3xx_freqs = freqs;
	pxa3xx_freqs_num = num;
	pxa3xx_freqs_table = table;

	return cpufreq_frequency_table_cpuinfo(policy, table);
}