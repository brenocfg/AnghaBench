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
typedef  int u8 ;
struct sensor_device_attribute_2 {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct abituguru_data {int** pwm_settings; int /*<<< orphan*/  update_lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ ABIT_UGURU_FAN_PWM ; 
 int ABIT_UGURU_FAN_PWM_ENABLE ; 
 size_t EINVAL ; 
 size_t EIO ; 
 int abituguru_write (struct abituguru_data*,scalar_t__,size_t,int*,int) ; 
 struct abituguru_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_pwm_enable(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = dev_get_drvdata(dev);
	u8 orig_val, user_val = simple_strtoul(buf, NULL, 10);
	ssize_t ret = count;

	mutex_lock(&data->update_lock);
	orig_val = data->pwm_settings[attr->index][0];
	switch (user_val) {
		case 0:
			data->pwm_settings[attr->index][0] &=
				~ABIT_UGURU_FAN_PWM_ENABLE;
			break;
		case 2:
			data->pwm_settings[attr->index][0] |=
				ABIT_UGURU_FAN_PWM_ENABLE;
			break;
		default:
			ret = -EINVAL;
	}
	if ((data->pwm_settings[attr->index][0] != orig_val) &&
			(abituguru_write(data, ABIT_UGURU_FAN_PWM + 1,
			attr->index, data->pwm_settings[attr->index],
			5) < 1)) {
		data->pwm_settings[attr->index][0] = orig_val;
		ret = -EIO;
	}
	mutex_unlock(&data->update_lock);
	return ret;
}