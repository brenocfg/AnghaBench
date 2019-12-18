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
typedef  int u16 ;
struct w83793_data {int** pwm; int /*<<< orphan*/ * pwm_stop_time; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PWM_STOP_TIME ; 
 int TIME_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct w83793_data* w83793_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_pwm(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	struct w83793_data *data = w83793_update_device(dev);
	u16 val;
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;

	if (PWM_STOP_TIME == nr)
		val = TIME_FROM_REG(data->pwm_stop_time[index]);
	else
		val = (data->pwm[index][nr] & 0x3f) << 2;

	return sprintf(buf, "%d\n", val);
}