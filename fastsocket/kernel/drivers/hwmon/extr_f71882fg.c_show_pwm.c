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
struct f71882fg_data {int pwm_enable; int* pwm; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_full_speed; int /*<<< orphan*/ * fan_target; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct f71882fg_data* f71882fg_update_device (struct device*) ; 
 int fan_from_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm(struct device *dev,
			struct device_attribute *devattr, char *buf)
{
	struct f71882fg_data *data = f71882fg_update_device(dev);
	int val, nr = to_sensor_dev_attr_2(devattr)->index;
	mutex_lock(&data->update_lock);
	if (data->pwm_enable & (1 << (2 * nr)))
		/* PWM mode */
		val = data->pwm[nr];
	else {
		/* RPM mode */
		val = 255 * fan_from_reg(data->fan_target[nr])
			/ fan_from_reg(data->fan_full_speed[nr]);
	}
	mutex_unlock(&data->update_lock);
	return sprintf(buf, "%d\n", val);
}