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
struct pcf8591_data {unsigned int aout; int /*<<< orphan*/  control; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct pcf8591_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_out0_output(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int value;
	struct i2c_client *client = to_i2c_client(dev);
	struct pcf8591_data *data = i2c_get_clientdata(client);
	if ((value = (simple_strtoul(buf, NULL, 10) + 5) / 10) <= 255) {
		data->aout = value;
		i2c_smbus_write_byte_data(client, data->control, data->aout);
		return count;
	}
	return -EINVAL;
}