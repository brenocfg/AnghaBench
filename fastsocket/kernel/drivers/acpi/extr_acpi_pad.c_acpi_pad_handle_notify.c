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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int acpi_pad_idle_cpus (int) ; 
 int /*<<< orphan*/  acpi_pad_idle_cpus_num () ; 
 int /*<<< orphan*/  acpi_pad_ost (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_pad_pur (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  isolated_cpus_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_pad_handle_notify(acpi_handle handle)
{
	int num_cpus = 0;
	int ret;
	uint32_t idle_cpus;

	mutex_lock(&isolated_cpus_lock);
	if (acpi_pad_pur(handle, &num_cpus)) {
		mutex_unlock(&isolated_cpus_lock);
		return;
	}
	ret = acpi_pad_idle_cpus(num_cpus);
	idle_cpus = acpi_pad_idle_cpus_num();
	if (!ret)
		acpi_pad_ost(handle, 0, idle_cpus);
	else
		acpi_pad_ost(handle, 1, 0);
	mutex_unlock(&isolated_cpus_lock);
}