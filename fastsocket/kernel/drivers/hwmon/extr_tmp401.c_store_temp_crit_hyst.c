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
struct tmp401_data {int config; int temp_crit_hyst; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_crit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 long SENSORS_LIMIT (long,int,int) ; 
 int TMP401_CONFIG_RANGE ; 
 int /*<<< orphan*/  TMP401_TEMP_CRIT_HYST ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 int tmp401_crit_register_to_temp (int /*<<< orphan*/ ,int) ; 
 struct tmp401_data* tmp401_update_device (struct device*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_temp_crit_hyst(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	int temp, index = to_sensor_dev_attr(devattr)->index;
	struct tmp401_data *data = tmp401_update_device(dev);
	long val;
	u8 reg;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	if (data->config & TMP401_CONFIG_RANGE)
		val = SENSORS_LIMIT(val, -64000, 191000);
	else
		val = SENSORS_LIMIT(val, 0, 127000);

	mutex_lock(&data->update_lock);
	temp = tmp401_crit_register_to_temp(data->temp_crit[index],
						data->config);
	val = SENSORS_LIMIT(val, temp - 255000, temp);
	reg = ((temp - val) + 500) / 1000;

	i2c_smbus_write_byte_data(to_i2c_client(dev),
		TMP401_TEMP_CRIT_HYST, reg);

	data->temp_crit_hyst = reg;

	mutex_unlock(&data->update_lock);

	return count;
}