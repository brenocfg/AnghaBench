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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct f71805f_data {int /*<<< orphan*/  update_lock; TYPE_1__* auto_points; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71805F_REG_PWM_AUTO_POINT_TEMP (int,int) ; 
 struct f71805f_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  f71805f_write8 (struct f71805f_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  temp_to_reg (unsigned long) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_auto_point_temp(struct device *dev,
				       struct device_attribute *devattr,
				       const char* buf, size_t count)
{
	struct f71805f_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	int pwmnr = attr->nr;
	int apnr = attr->index;
	unsigned long val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->auto_points[pwmnr].temp[apnr] = temp_to_reg(val);
	f71805f_write8(data, F71805F_REG_PWM_AUTO_POINT_TEMP(pwmnr, apnr),
		       data->auto_points[pwmnr].temp[apnr]);
	mutex_unlock(&data->update_lock);

	return count;
}