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
struct acpi_device {int dummy; } ;
struct acpi_bus_ops {int acpi_op_add; int acpi_op_start; } ;
typedef  int /*<<< orphan*/  ops ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_TYPE_POWER_BUTTON ; 
 int /*<<< orphan*/  ACPI_BUS_TYPE_SLEEP_BUTTON ; 
 int ACPI_FADT_POWER_BUTTON ; 
 int ACPI_FADT_SLEEP_BUTTON ; 
 int /*<<< orphan*/  ACPI_STA_DEFAULT ; 
 int acpi_add_single_object (struct acpi_device**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_bus_ops*) ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  memset (struct acpi_bus_ops*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int acpi_bus_scan_fixed(void)
{
	int result = 0;
	struct acpi_device *device = NULL;
	struct acpi_bus_ops ops;

	memset(&ops, 0, sizeof(ops));
	ops.acpi_op_add = 1;
	ops.acpi_op_start = 1;

	/*
	 * Enumerate all fixed-feature devices.
	 */
	if ((acpi_gbl_FADT.flags & ACPI_FADT_POWER_BUTTON) == 0) {
		result = acpi_add_single_object(&device, NULL,
						ACPI_BUS_TYPE_POWER_BUTTON,
						ACPI_STA_DEFAULT,
						&ops);
	}

	if ((acpi_gbl_FADT.flags & ACPI_FADT_SLEEP_BUTTON) == 0) {
		result = acpi_add_single_object(&device, NULL,
						ACPI_BUS_TYPE_SLEEP_BUTTON,
						ACPI_STA_DEFAULT,
						&ops);
	}

	return result;
}