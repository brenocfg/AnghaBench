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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  acpi_glue_data_handler ; 
 struct device* get_device (struct device*) ; 

struct device *acpi_get_physical_device(acpi_handle handle)
{
	acpi_status status;
	struct device *dev;

	status = acpi_get_data(handle, acpi_glue_data_handler, (void **)&dev);
	if (ACPI_SUCCESS(status))
		return get_device(dev);
	return NULL;
}