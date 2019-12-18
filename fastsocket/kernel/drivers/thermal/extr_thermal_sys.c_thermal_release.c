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
typedef  struct thermal_zone_device thermal_cooling_device ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  kfree (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 struct thermal_zone_device* to_cooling_device (struct device*) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static void thermal_release(struct device *dev)
{
	struct thermal_zone_device *tz;
	struct thermal_cooling_device *cdev;

	if (!strncmp(dev_name(dev), "thermal_zone", sizeof "thermal_zone" - 1)) {
		tz = to_thermal_zone(dev);
		kfree(tz);
	} else {
		cdev = to_cooling_device(dev);
		kfree(cdev);
	}
}