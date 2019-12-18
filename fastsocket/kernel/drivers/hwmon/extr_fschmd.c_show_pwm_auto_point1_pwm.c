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
struct fschmd_data {int* fan_min; int kind; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct fschmd_data* fschmd_update_device (struct device*) ; 
 int fscsyl ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm_auto_point1_pwm(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	int index = to_sensor_dev_attr(devattr)->index;
	struct fschmd_data *data = fschmd_update_device(dev);
	int val = data->fan_min[index];

	/* 0 = allow turning off (except on the syl), 1-255 = 50-100% */
	if (val || data->kind == fscsyl - 1)
		val = val / 2 + 128;

	return sprintf(buf, "%d\n", val);
}