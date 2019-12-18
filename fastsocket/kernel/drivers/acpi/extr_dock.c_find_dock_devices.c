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
typedef  int /*<<< orphan*/  u32 ;
struct dock_station {scalar_t__ handle; } ;
struct dock_dependent_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_bus_get_ejd (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_get_parent (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  add_dock_dependent_device (struct dock_station*,struct dock_dependent_device*) ; 
 struct dock_dependent_device* alloc_dock_dependent_device (scalar_t__) ; 

__attribute__((used)) static acpi_status
find_dock_devices(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	acpi_status status;
	acpi_handle tmp, parent;
	struct dock_station *ds = context;
	struct dock_dependent_device *dd;

	status = acpi_bus_get_ejd(handle, &tmp);
	if (ACPI_FAILURE(status)) {
		/* try the parent device as well */
		status = acpi_get_parent(handle, &parent);
		if (ACPI_FAILURE(status))
			goto fdd_out;
		/* see if parent is dependent on dock */
		status = acpi_bus_get_ejd(parent, &tmp);
		if (ACPI_FAILURE(status))
			goto fdd_out;
	}

	if (tmp == ds->handle) {
		dd = alloc_dock_dependent_device(handle);
		if (dd)
			add_dock_dependent_device(ds, dd);
	}
fdd_out:
	return AE_OK;
}