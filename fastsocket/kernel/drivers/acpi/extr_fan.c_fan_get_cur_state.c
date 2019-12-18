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
struct thermal_cooling_device {struct acpi_device* devdata; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3 ; 
 int EINVAL ; 
 int acpi_bus_get_power (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fan_get_cur_state(struct thermal_cooling_device *cdev, unsigned long
			     *state)
{
	struct acpi_device *device = cdev->devdata;
	int result;
	int acpi_state;

	if (!device)
		return -EINVAL;

	result = acpi_bus_get_power(device->handle, &acpi_state);
	if (result)
		return result;

	*state = (acpi_state == ACPI_STATE_D3 ? 0 :
		 (acpi_state == ACPI_STATE_D0 ? 1 : -1));
	return 0;
}