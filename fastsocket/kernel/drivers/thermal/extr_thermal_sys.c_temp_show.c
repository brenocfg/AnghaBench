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
struct thermal_zone_device {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* get_temp ) (struct thermal_zone_device*,long*) ;} ;

/* Variables and functions */
 int EPERM ; 
 int sprintf (char*,char*,long) ; 
 int stub1 (struct thermal_zone_device*,long*) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static ssize_t
temp_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	long temperature;
	int ret;

	if (!tz->ops->get_temp)
		return -EPERM;

	ret = tz->ops->get_temp(tz, &temperature);

	if (ret)
		return ret;

	return sprintf(buf, "%ld\n", temperature);
}