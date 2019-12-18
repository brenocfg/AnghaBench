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
typedef  scalar_t__ u32 ;
struct acpi_device {struct acpi_device* parent; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_object_type ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ *,struct acpi_device**) ; 
 int acpi_bus_remove (struct acpi_device*,int) ; 
 int /*<<< orphan*/  acpi_get_next_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  acpi_get_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int acpi_bus_trim(struct acpi_device *start, int rmdevice)
{
	acpi_status status;
	struct acpi_device *parent, *child;
	acpi_handle phandle, chandle;
	acpi_object_type type;
	u32 level = 1;
	int err = 0;

	parent = start;
	phandle = start->handle;
	child = chandle = NULL;

	while ((level > 0) && parent && (!err)) {
		status = acpi_get_next_object(ACPI_TYPE_ANY, phandle,
					      chandle, &chandle);

		/*
		 * If this scope is exhausted then move our way back up.
		 */
		if (ACPI_FAILURE(status)) {
			level--;
			chandle = phandle;
			acpi_get_parent(phandle, &phandle);
			child = parent;
			parent = parent->parent;

			if (level == 0)
				err = acpi_bus_remove(child, rmdevice);
			else
				err = acpi_bus_remove(child, 1);

			continue;
		}

		status = acpi_get_type(chandle, &type);
		if (ACPI_FAILURE(status)) {
			continue;
		}
		/*
		 * If there is a device corresponding to chandle then
		 * parse it (depth-first).
		 */
		if (acpi_bus_get_device(chandle, &child) == 0) {
			level++;
			phandle = chandle;
			chandle = NULL;
			parent = child;
		}
		continue;
	}
	return err;
}