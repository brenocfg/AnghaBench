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
struct sensor_device_attribute {int index; } ;
struct it87_data {int fan_main_ctrl; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * manual_pwm_ctl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  IT87_REG_FAN_CTL ; 
 int /*<<< orphan*/  IT87_REG_FAN_MAIN_CTRL ; 
 int /*<<< orphan*/  IT87_REG_PWM (int) ; 
 int PWM_TO_REG (int /*<<< orphan*/ ) ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 int it87_read_value (struct it87_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_enable(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;

	struct it87_data *data = dev_get_drvdata(dev);
	int val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);

	if (val == 0) {
		int tmp;
		/* make sure the fan is on when in on/off mode */
		tmp = it87_read_value(data, IT87_REG_FAN_CTL);
		it87_write_value(data, IT87_REG_FAN_CTL, tmp | (1 << nr));
		/* set on/off mode */
		data->fan_main_ctrl &= ~(1 << nr);
		it87_write_value(data, IT87_REG_FAN_MAIN_CTRL, data->fan_main_ctrl);
	} else if (val == 1) {
		/* set SmartGuardian mode */
		data->fan_main_ctrl |= (1 << nr);
		it87_write_value(data, IT87_REG_FAN_MAIN_CTRL, data->fan_main_ctrl);
		/* set saved pwm value, clear FAN_CTLX PWM mode bit */
		it87_write_value(data, IT87_REG_PWM(nr), PWM_TO_REG(data->manual_pwm_ctl[nr]));
	} else {
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	mutex_unlock(&data->update_lock);
	return count;
}