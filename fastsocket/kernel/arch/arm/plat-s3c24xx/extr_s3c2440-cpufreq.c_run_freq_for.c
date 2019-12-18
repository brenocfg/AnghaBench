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
struct cpufreq_frequency_table {int dummy; } ;

/* Variables and functions */
 int s3c_cpufreq_addfreq (struct cpufreq_frequency_table*,int,size_t,unsigned long) ; 

__attribute__((used)) static int run_freq_for(unsigned long max_hclk, unsigned long fclk,
			int *divs,
			struct cpufreq_frequency_table *table,
			size_t table_size)
{
	unsigned long freq;
	int index = 0;
	int div;

	for (div = *divs; div > 0; div = *divs++) {
		freq = fclk / div;

		if (freq > max_hclk && div != 1)
			continue;

		freq /= 1000; /* table is in kHz */
		index = s3c_cpufreq_addfreq(table, index, table_size, freq);
		if (index < 0)
			break;
	}

	return index;
}