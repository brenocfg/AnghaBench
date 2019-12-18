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
struct acpi_container {int dummy; } ;
typedef  int acpi_status ;

/* Variables and functions */
 int AE_OK ; 
 struct acpi_container* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  kfree (struct acpi_container*) ; 

__attribute__((used)) static int acpi_container_remove(struct acpi_device *device, int type)
{
	acpi_status status = AE_OK;
	struct acpi_container *pc = NULL;

	pc = acpi_driver_data(device);
	kfree(pc);
	return status;
}