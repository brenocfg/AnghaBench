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
struct acpi_thermal {int /*<<< orphan*/  thermal_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_thermal_check(void *data)
{
	struct acpi_thermal *tz = data;

	thermal_zone_device_update(tz->thermal_zone);
}