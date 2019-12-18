#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int count; union acpi_object* elements; } ;
struct TYPE_6__ {scalar_t__ value; } ;
union acpi_object {scalar_t__ type; TYPE_5__ reference; TYPE_2__ package; TYPE_1__ integer; } ;
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int count; int /*<<< orphan*/ * handles; } ;
struct TYPE_9__ {TYPE_3__ resources; scalar_t__ sleep_state; scalar_t__ gpe_number; int /*<<< orphan*/  gpe_device; } ;
struct acpi_device {TYPE_4__ wakeup; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int ACPI_MAX_HANDLES ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_BAD_DATA ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 

__attribute__((used)) static acpi_status
acpi_bus_extract_wakeup_device_power_package(struct acpi_device *device,
					     union acpi_object *package)
{
	int i = 0;
	union acpi_object *element = NULL;

	if (!device || !package || (package->package.count < 2))
		return AE_BAD_PARAMETER;

	element = &(package->package.elements[0]);
	if (!element)
		return AE_BAD_PARAMETER;
	if (element->type == ACPI_TYPE_PACKAGE) {
		if ((element->package.count < 2) ||
		    (element->package.elements[0].type !=
		     ACPI_TYPE_LOCAL_REFERENCE)
		    || (element->package.elements[1].type != ACPI_TYPE_INTEGER))
			return AE_BAD_DATA;
		device->wakeup.gpe_device =
		    element->package.elements[0].reference.handle;
		device->wakeup.gpe_number =
		    (u32) element->package.elements[1].integer.value;
	} else if (element->type == ACPI_TYPE_INTEGER) {
		device->wakeup.gpe_number = element->integer.value;
	} else
		return AE_BAD_DATA;

	element = &(package->package.elements[1]);
	if (element->type != ACPI_TYPE_INTEGER) {
		return AE_BAD_DATA;
	}
	device->wakeup.sleep_state = element->integer.value;

	if ((package->package.count - 2) > ACPI_MAX_HANDLES) {
		return AE_NO_MEMORY;
	}
	device->wakeup.resources.count = package->package.count - 2;
	for (i = 0; i < device->wakeup.resources.count; i++) {
		element = &(package->package.elements[i + 2]);
		if (element->type != ACPI_TYPE_LOCAL_REFERENCE)
			return AE_BAD_DATA;

		device->wakeup.resources.handles[i] = element->reference.handle;
	}

	return AE_OK;
}