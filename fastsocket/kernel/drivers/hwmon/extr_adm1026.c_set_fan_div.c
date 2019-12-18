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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1026_data {int* fan_div; int /*<<< orphan*/  update_lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_FAN_DIV_0_3 ; 
 int /*<<< orphan*/  ADM1026_REG_FAN_DIV_4_7 ; 
 int DIV_FROM_REG (int) ; 
 int DIV_TO_REG (int) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fixup_fan_min (struct device*,int,int) ; 
 struct adm1026_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1026_data *data = i2c_get_clientdata(client);
	int val, orig_div, new_div, shift;

	val = simple_strtol(buf, NULL, 10);
	new_div = DIV_TO_REG(val);
	if (new_div == 0) {
		return -EINVAL;
	}
	mutex_lock(&data->update_lock);
	orig_div = data->fan_div[nr];
	data->fan_div[nr] = DIV_FROM_REG(new_div);

	if (nr < 4) { /* 0 <= nr < 4 */
		shift = 2 * nr;
		adm1026_write_value(client, ADM1026_REG_FAN_DIV_0_3,
			((DIV_TO_REG(orig_div) & (~(0x03 << shift))) |
			(new_div << shift)));
	} else { /* 3 < nr < 8 */
		shift = 2 * (nr - 4);
		adm1026_write_value(client, ADM1026_REG_FAN_DIV_4_7,
			((DIV_TO_REG(orig_div) & (~(0x03 << (2 * shift)))) |
			(new_div << shift)));
	}

	if (data->fan_div[nr] != orig_div) {
		fixup_fan_min(dev, nr, orig_div);
	}
	mutex_unlock(&data->update_lock);
	return count;
}