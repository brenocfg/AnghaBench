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
struct acpi_device {int dummy; } ;
struct acpi_button {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACPI_BUTTON_TYPE_LID ; 
 struct acpi_button* acpi_driver_data (struct acpi_device*) ; 
 int acpi_lid_send_state (struct acpi_device*) ; 

__attribute__((used)) static int acpi_button_resume(struct acpi_device *device)
{
	struct acpi_button *button = acpi_driver_data(device);

	if (button->type == ACPI_BUTTON_TYPE_LID)
		return acpi_lid_send_state(device);
	return 0;
}