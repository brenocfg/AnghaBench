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
struct smsc47m1_data {int* pwm; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/ * SMSC47M1_REG_PWM ; 
 struct smsc47m1_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smsc47m1_write_value (struct smsc47m1_data*,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_en(struct device *dev, struct device_attribute
			  *devattr, const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct smsc47m1_data *data = dev_get_drvdata(dev);
	int nr = attr->index;
	long val = simple_strtol(buf, NULL, 10);
	
	if (val != 0 && val != 1)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] &= 0xFE; /* preserve the other bits */
	data->pwm[nr] |= !val;
	smsc47m1_write_value(data, SMSC47M1_REG_PWM[nr],
			     data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	return count;
}