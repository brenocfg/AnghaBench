#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {struct acpi_thermal* devdata; } ;
struct TYPE_4__ {scalar_t__ valid; } ;
struct TYPE_5__ {int /*<<< orphan*/  temperature; TYPE_1__ flags; } ;
struct TYPE_6__ {TYPE_2__ critical; } ;
struct acpi_thermal {int /*<<< orphan*/  kelvin_offset; TYPE_3__ trips; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long KELVIN_TO_MILLICELSIUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thermal_get_crit_temp(struct thermal_zone_device *thermal,
				unsigned long *temperature) {
	struct acpi_thermal *tz = thermal->devdata;

	if (tz->trips.critical.flags.valid) {
		*temperature = KELVIN_TO_MILLICELSIUS(
				tz->trips.critical.temperature,
				tz->kelvin_offset);
		return 0;
	} else
		return -EINVAL;
}