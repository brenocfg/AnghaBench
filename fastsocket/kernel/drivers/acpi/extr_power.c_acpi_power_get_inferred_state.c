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
struct acpi_handle_list {int count; } ;
struct TYPE_4__ {int state; TYPE_1__* states; } ;
struct acpi_device {TYPE_2__ power; } ;
struct TYPE_3__ {struct acpi_handle_list resources; } ;

/* Variables and functions */
 int ACPI_POWER_RESOURCE_STATE_ON ; 
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3 ; 
 int ACPI_STATE_UNKNOWN ; 
 int EINVAL ; 
 int acpi_power_get_list_state (struct acpi_handle_list*,int*) ; 

int acpi_power_get_inferred_state(struct acpi_device *device)
{
	int result = 0;
	struct acpi_handle_list *list = NULL;
	int list_state = 0;
	int i = 0;


	if (!device)
		return -EINVAL;

	device->power.state = ACPI_STATE_UNKNOWN;

	/*
	 * We know a device's inferred power state when all the resources
	 * required for a given D-state are 'on'.
	 */
	for (i = ACPI_STATE_D0; i < ACPI_STATE_D3; i++) {
		list = &device->power.states[i].resources;
		if (list->count < 1)
			continue;

		result = acpi_power_get_list_state(list, &list_state);
		if (result)
			return result;

		if (list_state == ACPI_POWER_RESOURCE_STATE_ON) {
			device->power.state = i;
			return 0;
		}
	}

	device->power.state = ACPI_STATE_D3;

	return 0;
}