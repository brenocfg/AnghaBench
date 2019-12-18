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
struct thermal_zone_device {int dummy; } ;
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 int acpi_thermal_cooling_device_cb (struct thermal_zone_device*,struct thermal_cooling_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_bind_cooling_device ; 

__attribute__((used)) static int
acpi_thermal_bind_cooling_device(struct thermal_zone_device *thermal,
					struct thermal_cooling_device *cdev)
{
	return acpi_thermal_cooling_device_cb(thermal, cdev,
				thermal_zone_bind_cooling_device);
}