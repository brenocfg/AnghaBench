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
struct cpufreq_policy {size_t cpu; } ;
struct cpufreq_acpi_io {int /*<<< orphan*/  acpi_data; } ;

/* Variables and functions */
 struct cpufreq_acpi_io** acpi_io_data ; 
 int /*<<< orphan*/  acpi_processor_unregister_performance (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_put_attr (size_t) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  kfree (struct cpufreq_acpi_io*) ; 

__attribute__((used)) static int
acpi_cpufreq_cpu_exit (
	struct cpufreq_policy   *policy)
{
	struct cpufreq_acpi_io *data = acpi_io_data[policy->cpu];

	dprintk("acpi_cpufreq_cpu_exit\n");

	if (data) {
		cpufreq_frequency_table_put_attr(policy->cpu);
		acpi_io_data[policy->cpu] = NULL;
		acpi_processor_unregister_performance(&data->acpi_data,
		                                      policy->cpu);
		kfree(data);
	}

	return (0);
}