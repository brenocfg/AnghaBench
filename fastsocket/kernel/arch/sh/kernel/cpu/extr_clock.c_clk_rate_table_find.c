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
struct cpufreq_frequency_table {unsigned long frequency; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned long CPUFREQ_ENTRY_INVALID ; 
 unsigned long CPUFREQ_TABLE_END ; 
 int ENOENT ; 

int clk_rate_table_find(struct clk *clk,
			struct cpufreq_frequency_table *freq_table,
			unsigned long rate)
{
	int i;

	for (i = 0; freq_table[i].frequency != CPUFREQ_TABLE_END; i++) {
		unsigned long freq = freq_table[i].frequency;

		if (freq == CPUFREQ_ENTRY_INVALID)
			continue;

		if (freq == rate)
			return i;
	}

	return -ENOENT;
}