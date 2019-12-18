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
struct TYPE_2__ {int /*<<< orphan*/  shared_cpu_map; scalar_t__ state_count; } ;
struct powernow_k8_data {TYPE_1__ acpi_data; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_processor_unregister_performance (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void powernow_k8_cpu_exit_acpi(struct powernow_k8_data *data)
{
	if (data->acpi_data.state_count)
		acpi_processor_unregister_performance(&data->acpi_data,
				data->cpu);
	free_cpumask_var(data->acpi_data.shared_cpu_map);
}