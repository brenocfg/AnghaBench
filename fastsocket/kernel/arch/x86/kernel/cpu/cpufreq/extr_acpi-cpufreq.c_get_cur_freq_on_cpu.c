#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_cpufreq_data {int resume; TYPE_1__* acpi_data; TYPE_2__* freq_table; } ;
struct TYPE_4__ {unsigned int frequency; } ;
struct TYPE_3__ {size_t state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  drv_data ; 
 unsigned int extract_freq (int /*<<< orphan*/ ,struct acpi_cpufreq_data*) ; 
 int /*<<< orphan*/  get_cur_val (int /*<<< orphan*/ ) ; 
 struct acpi_cpufreq_data* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int get_cur_freq_on_cpu(unsigned int cpu)
{
	struct acpi_cpufreq_data *data = per_cpu(drv_data, cpu);
	unsigned int freq;
	unsigned int cached_freq;

	dprintk("get_cur_freq_on_cpu (%d)\n", cpu);

	if (unlikely(data == NULL ||
		     data->acpi_data == NULL || data->freq_table == NULL)) {
		return 0;
	}

	cached_freq = data->freq_table[data->acpi_data->state].frequency;
	freq = extract_freq(get_cur_val(cpumask_of(cpu)), data);
	if (freq != cached_freq) {
		/*
		 * The dreaded BIOS frequency change behind our back.
		 * Force set the frequency on next target call.
		 */
		data->resume = 1;
	}

	dprintk("cur freq = %u\n", freq);

	return freq;
}