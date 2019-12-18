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
typedef  int u32 ;
struct w83793_data {int* temp_fan_map; int pwm_enable; int* temp_cruise; int* tolerance; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int TEMP_CRUISE ; 
 int TEMP_FAN_MAP ; 
 int TEMP_PWM_ENABLE ; 
 int TEMP_TO_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  W83793_REG_PWM_ENABLE ; 
 int /*<<< orphan*/  W83793_REG_TEMP_CRUISE (int) ; 
 int /*<<< orphan*/  W83793_REG_TEMP_FAN_MAP (int) ; 
 int /*<<< orphan*/  W83793_REG_TEMP_TOL (int) ; 
 struct w83793_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 void* w83793_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83793_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_sf_ctrl(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83793_data *data = i2c_get_clientdata(client);
	u32 val;

	mutex_lock(&data->update_lock);
	if (TEMP_FAN_MAP == nr) {
		val = simple_strtoul(buf, NULL, 10) & 0xff;
		w83793_write_value(client, W83793_REG_TEMP_FAN_MAP(index), val);
		data->temp_fan_map[index] = val;
	} else if (TEMP_PWM_ENABLE == nr) {
		val = simple_strtoul(buf, NULL, 10);
		if (2 == val || 3 == val) {
			data->pwm_enable =
			    w83793_read_value(client, W83793_REG_PWM_ENABLE);
			if (val - 2)
				data->pwm_enable |= 1 << index;
			else
				data->pwm_enable &= ~(1 << index);
			w83793_write_value(client, W83793_REG_PWM_ENABLE,
							data->pwm_enable);
		} else {
			mutex_unlock(&data->update_lock);
			return -EINVAL;
		}
	} else if (TEMP_CRUISE == nr) {
		data->temp_cruise[index] =
		    w83793_read_value(client, W83793_REG_TEMP_CRUISE(index));
		val = TEMP_TO_REG(simple_strtol(buf, NULL, 10), 0, 0x7f);
		data->temp_cruise[index] &= 0x80;
		data->temp_cruise[index] |= val;

		w83793_write_value(client, W83793_REG_TEMP_CRUISE(index),
						data->temp_cruise[index]);
	} else {		/* TEMP_TOLERANCE */
		int i = index >> 1;
		u8 shift = (index & 0x01) ? 4 : 0;
		data->tolerance[i] =
		    w83793_read_value(client, W83793_REG_TEMP_TOL(i));

		val = TEMP_TO_REG(simple_strtol(buf, NULL, 10), 0, 0x0f);
		data->tolerance[i] &= ~(0x0f << shift);
		data->tolerance[i] |= val << shift;
		w83793_write_value(client, W83793_REG_TEMP_TOL(i),
							data->tolerance[i]);
	}

	mutex_unlock(&data->update_lock);
	return count;
}