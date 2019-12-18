#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_frequency_table {int index; unsigned long frequency; } ;
struct clk_div_mult_table {unsigned long* divisors; int nr_divisors; unsigned long* multipliers; int nr_multipliers; } ;
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 unsigned long CPUFREQ_ENTRY_INVALID ; 
 unsigned long CPUFREQ_TABLE_END ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

void clk_rate_table_build(struct clk *clk,
			  struct cpufreq_frequency_table *freq_table,
			  int nr_freqs,
			  struct clk_div_mult_table *src_table,
			  unsigned long *bitmap)
{
	unsigned long mult, div;
	unsigned long freq;
	int i;

	for (i = 0; i < nr_freqs; i++) {
		div = 1;
		mult = 1;

		if (src_table->divisors && i < src_table->nr_divisors)
			div = src_table->divisors[i];

		if (src_table->multipliers && i < src_table->nr_multipliers)
			mult = src_table->multipliers[i];

		if (!div || !mult || (bitmap && !test_bit(i, bitmap)))
			freq = CPUFREQ_ENTRY_INVALID;
		else
			freq = clk->parent->rate * mult / div;

		freq_table[i].index = i;
		freq_table[i].frequency = freq;
	}

	/* Termination entry */
	freq_table[i].index = i;
	freq_table[i].frequency = CPUFREQ_TABLE_END;
}