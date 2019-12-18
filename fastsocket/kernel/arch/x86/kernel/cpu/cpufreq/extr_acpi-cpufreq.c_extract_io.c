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
typedef  scalar_t__ u32 ;
struct acpi_processor_performance {int state_count; TYPE_1__* states; } ;
struct acpi_cpufreq_data {TYPE_2__* freq_table; struct acpi_processor_performance* acpi_data; } ;
struct TYPE_4__ {int frequency; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */

__attribute__((used)) static unsigned extract_io(u32 value, struct acpi_cpufreq_data *data)
{
	struct acpi_processor_performance *perf;
	int i;

	perf = data->acpi_data;

	for (i = 0; i < perf->state_count; i++) {
		if (value == perf->states[i].status)
			return data->freq_table[i].frequency;
	}
	return 0;
}