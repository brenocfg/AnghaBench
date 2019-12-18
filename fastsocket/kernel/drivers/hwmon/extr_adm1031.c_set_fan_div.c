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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1031_data {int* fan_div; int* fan_min; int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1031_REG_FAN_DIV (int) ; 
 int /*<<< orphan*/  ADM1031_REG_FAN_MIN (int) ; 
 size_t EINVAL ; 
 int FAN_DIV_FROM_REG (int) ; 
 void* adm1031_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1031_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adm1031_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1031_data *data = i2c_get_clientdata(client);
	int nr = to_sensor_dev_attr(attr)->index;
	int val = simple_strtol(buf, NULL, 10);
	u8 tmp;
	int old_div;
	int new_min;

	tmp = val == 8 ? 0xc0 :
	      val == 4 ? 0x80 :
	      val == 2 ? 0x40 :
	      val == 1 ? 0x00 :
	      0xff;
	if (tmp == 0xff)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	/* Get fresh readings */
	data->fan_div[nr] = adm1031_read_value(client,
					       ADM1031_REG_FAN_DIV(nr));
	data->fan_min[nr] = adm1031_read_value(client,
					       ADM1031_REG_FAN_MIN(nr));

	/* Write the new clock divider and fan min */
	old_div = FAN_DIV_FROM_REG(data->fan_div[nr]);
	data->fan_div[nr] = tmp | (0x3f & data->fan_div[nr]);
	new_min = data->fan_min[nr] * old_div / val;
	data->fan_min[nr] = new_min > 0xff ? 0xff : new_min;

	adm1031_write_value(client, ADM1031_REG_FAN_DIV(nr),
			    data->fan_div[nr]);
	adm1031_write_value(client, ADM1031_REG_FAN_MIN(nr),
			    data->fan_min[nr]);

	/* Invalidate the cache: fan speed is no longer valid */
	data->valid = 0;
	mutex_unlock(&data->update_lock);
	return count;
}