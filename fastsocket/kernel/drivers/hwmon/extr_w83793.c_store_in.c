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
typedef  int u32 ;
struct w83793_data {int* in_low_bits; int** in; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** W83793_REG_IN ; 
 int /*<<< orphan*/ * W83793_REG_IN_LOW_BITS ; 
 struct w83793_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* scale_in ; 
 int* scale_in_add ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83793_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83793_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_in(struct device *dev, struct device_attribute *attr,
	 const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83793_data *data = i2c_get_clientdata(client);
	u32 val;

	val =
	    (simple_strtoul(buf, NULL, 10) +
	     scale_in[index] / 2) / scale_in[index];
	mutex_lock(&data->update_lock);
	if (index > 2) {
		/* fix the limit values of 5VDD and 5VSB to ALARM mechanism */
		if (1 == nr || 2 == nr) {
			val -= scale_in_add[index] / scale_in[index];
		}
		val = SENSORS_LIMIT(val, 0, 255);
	} else {
		val = SENSORS_LIMIT(val, 0, 0x3FF);
		data->in_low_bits[nr] =
		    w83793_read_value(client, W83793_REG_IN_LOW_BITS[nr]);
		data->in_low_bits[nr] &= ~(0x03 << (2 * index));
		data->in_low_bits[nr] |= (val & 0x03) << (2 * index);
		w83793_write_value(client, W83793_REG_IN_LOW_BITS[nr],
						     data->in_low_bits[nr]);
		val >>= 2;
	}
	data->in[index][nr] = val;
	w83793_write_value(client, W83793_REG_IN[index][nr],
							data->in[index][nr]);
	mutex_unlock(&data->update_lock);
	return count;
}