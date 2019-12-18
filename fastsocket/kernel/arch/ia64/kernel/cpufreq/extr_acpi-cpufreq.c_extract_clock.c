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
struct TYPE_3__ {unsigned long state_count; TYPE_2__* states; } ;
struct cpufreq_acpi_io {TYPE_1__ acpi_data; } ;
struct TYPE_4__ {unsigned int status; int core_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static unsigned
extract_clock (
	struct cpufreq_acpi_io *data,
	unsigned value,
	unsigned int cpu)
{
	unsigned long i;

	dprintk("extract_clock\n");

	for (i = 0; i < data->acpi_data.state_count; i++) {
		if (value == data->acpi_data.states[i].status)
			return data->acpi_data.states[i].core_frequency;
	}
	return data->acpi_data.states[i-1].core_frequency;
}