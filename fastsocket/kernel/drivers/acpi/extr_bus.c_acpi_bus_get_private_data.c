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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_bus_private_data_handler ; 
 int /*<<< orphan*/  acpi_get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

int acpi_bus_get_private_data(acpi_handle handle, void **data)
{
	acpi_status status = AE_OK;

	if (!*data)
		return -EINVAL;

	status = acpi_get_data(handle, acpi_bus_private_data_handler, data);
	if (ACPI_FAILURE(status) || !*data) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "No context for object [%p]\n",
				handle));
		return -ENODEV;
	}

	return 0;
}