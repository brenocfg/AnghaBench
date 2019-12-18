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
struct sensor_device_attribute {size_t index; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1029_data {int /*<<< orphan*/  update_lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ADM1029_REG_FAN_DIV ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 struct adm1029_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev,
	    struct device_attribute *devattr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1029_data *data = i2c_get_clientdata(client);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	long val = simple_strtol(buf, NULL, 10);
	u8 reg;

	mutex_lock(&data->update_lock);

	/*Read actual config */
	reg = i2c_smbus_read_byte_data(client,
				       ADM1029_REG_FAN_DIV[attr->index]);

	switch (val) {
	case 1:
		val = 1;
		break;
	case 2:
		val = 2;
		break;
	case 4:
		val = 3;
		break;
	default:
		mutex_unlock(&data->update_lock);
		dev_err(&client->dev, "fan_div value %ld not "
			"supported. Choose one of 1, 2 or 4!\n", val);
		return -EINVAL;
	}
	/* Update the value */
	reg = (reg & 0x3F) | (val << 6);

	/* Write value */
	i2c_smbus_write_byte_data(client,
				  ADM1029_REG_FAN_DIV[attr->index], reg);
	mutex_unlock(&data->update_lock);

	return count;
}