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
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_STATE_D0 ; 
 int AE_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_bus_set_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_fan_suspend(struct acpi_device *device, pm_message_t state)
{
	if (!device)
		return -EINVAL;

	acpi_bus_set_power(device->handle, ACPI_STATE_D0);

	return AE_OK;
}