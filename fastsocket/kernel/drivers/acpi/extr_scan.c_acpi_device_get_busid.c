#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bus_id; } ;
struct acpi_device {int device_type; TYPE_1__ pnp; int /*<<< orphan*/  handle; } ;
struct acpi_buffer {int member_0; char* member_1; } ;
typedef  int /*<<< orphan*/  bus_id ;

/* Variables and functions */
#define  ACPI_BUS_TYPE_POWER_BUTTON 129 
#define  ACPI_BUS_TYPE_SLEEP_BUTTON 128 
 scalar_t__ ACPI_IS_ROOT_DEVICE (struct acpi_device*) ; 
 int /*<<< orphan*/  ACPI_SINGLE_NAME ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acpi_device_get_busid(struct acpi_device *device)
{
	char bus_id[5] = { '?', 0 };
	struct acpi_buffer buffer = { sizeof(bus_id), bus_id };
	int i = 0;

	/*
	 * Bus ID
	 * ------
	 * The device's Bus ID is simply the object name.
	 * TBD: Shouldn't this value be unique (within the ACPI namespace)?
	 */
	if (ACPI_IS_ROOT_DEVICE(device)) {
		strcpy(device->pnp.bus_id, "ACPI");
		return;
	}

	switch (device->device_type) {
	case ACPI_BUS_TYPE_POWER_BUTTON:
		strcpy(device->pnp.bus_id, "PWRF");
		break;
	case ACPI_BUS_TYPE_SLEEP_BUTTON:
		strcpy(device->pnp.bus_id, "SLPF");
		break;
	default:
		acpi_get_name(device->handle, ACPI_SINGLE_NAME, &buffer);
		/* Clean up trailing underscores (if any) */
		for (i = 3; i > 1; i--) {
			if (bus_id[i] == '_')
				bus_id[i] = '\0';
			else
				break;
		}
		strcpy(device->pnp.bus_id, bus_id);
		break;
	}
}