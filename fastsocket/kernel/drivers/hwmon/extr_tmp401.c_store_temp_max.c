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
typedef  int u16 ;
struct tmp401_data {int* temp_high; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/ * TMP401_TEMP_HIGH_LIMIT_LSB ; 
 int /*<<< orphan*/ * TMP401_TEMP_HIGH_LIMIT_MSB_WRITE ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 int tmp401_temp_to_register (long,int /*<<< orphan*/ ) ; 
 struct tmp401_data* tmp401_update_device (struct device*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_temp_max(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	int index = to_sensor_dev_attr(devattr)->index;
	struct tmp401_data *data = tmp401_update_device(dev);
	long val;
	u16 reg;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	reg = tmp401_temp_to_register(val, data->config);

	mutex_lock(&data->update_lock);

	i2c_smbus_write_byte_data(to_i2c_client(dev),
		TMP401_TEMP_HIGH_LIMIT_MSB_WRITE[index], reg >> 8);
	i2c_smbus_write_byte_data(to_i2c_client(dev),
		TMP401_TEMP_HIGH_LIMIT_LSB[index], reg & 0xFF);

	data->temp_high[index] = reg;

	mutex_unlock(&data->update_lock);

	return count;
}