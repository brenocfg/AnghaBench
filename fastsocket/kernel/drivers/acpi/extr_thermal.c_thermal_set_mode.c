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
struct thermal_zone_device {struct acpi_thermal* devdata; } ;
struct acpi_thermal {int tz_enabled; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int THERMAL_DEVICE_DISABLED ; 
 int THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  acpi_thermal_check (struct acpi_thermal*) ; 
 int /*<<< orphan*/  disabled ; 
 int /*<<< orphan*/  enabled ; 

__attribute__((used)) static int thermal_set_mode(struct thermal_zone_device *thermal,
				enum thermal_device_mode mode)
{
	struct acpi_thermal *tz = thermal->devdata;
	int enable;

	if (!tz)
		return -EINVAL;

	/*
	 * enable/disable thermal management from ACPI thermal driver
	 */
	if (mode == THERMAL_DEVICE_ENABLED)
		enable = 1;
	else if (mode == THERMAL_DEVICE_DISABLED)
		enable = 0;
	else
		return -EINVAL;

	if (enable != tz->tz_enabled) {
		tz->tz_enabled = enable;
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			"%s ACPI thermal control\n",
			tz->tz_enabled ? enabled : disabled));
		acpi_thermal_check(tz);
	}
	return 0;
}