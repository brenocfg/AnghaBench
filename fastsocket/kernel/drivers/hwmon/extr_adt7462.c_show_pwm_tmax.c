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
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7462_data {size_t* pwm_trange; int* pwm_tmin; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t ADT7462_PWM_RANGE_SHIFT ; 
 struct adt7462_data* adt7462_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int* trange_values ; 

__attribute__((used)) static ssize_t show_pwm_tmax(struct device *dev,
			     struct device_attribute *devattr,
			     char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7462_data *data = adt7462_update_device(dev);

	/* tmax = tmin + trange */
	int trange = trange_values[data->pwm_trange[attr->index] >>
				   ADT7462_PWM_RANGE_SHIFT];
	int tmin = (data->pwm_tmin[attr->index] - 64) * 1000;

	return sprintf(buf, "%d\n", tmin + trange);
}