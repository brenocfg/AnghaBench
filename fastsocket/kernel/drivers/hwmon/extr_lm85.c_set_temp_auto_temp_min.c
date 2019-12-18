#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm85_data {int* pwm_freq; int /*<<< orphan*/  update_lock; TYPE_1__* zone; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int limit; int range; int max_desired; int hyst; int off_desired; } ;

/* Variables and functions */
 int HYST_TO_REG (scalar_t__) ; 
 int /*<<< orphan*/  LM85_REG_AFAN_HYST1 ; 
 int /*<<< orphan*/  LM85_REG_AFAN_HYST2 ; 
 int /*<<< orphan*/  LM85_REG_AFAN_LIMIT (int) ; 
 int /*<<< orphan*/  LM85_REG_AFAN_RANGE (int) ; 
 int RANGE_TO_REG (scalar_t__) ; 
 scalar_t__ TEMP_FROM_REG (int) ; 
 int TEMP_TO_REG (long) ; 
 struct lm85_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lm85_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp_auto_temp_min(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct lm85_data *data = i2c_get_clientdata(client);
	long val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->zone[nr].limit = TEMP_TO_REG(val);
	lm85_write_value(client, LM85_REG_AFAN_LIMIT(nr),
		data->zone[nr].limit);

/* Update temp_auto_max and temp_auto_range */
	data->zone[nr].range = RANGE_TO_REG(
		TEMP_FROM_REG(data->zone[nr].max_desired) -
		TEMP_FROM_REG(data->zone[nr].limit));
	lm85_write_value(client, LM85_REG_AFAN_RANGE(nr),
		((data->zone[nr].range & 0x0f) << 4)
		| (data->pwm_freq[nr] & 0x07));

/* Update temp_auto_hyst and temp_auto_off */
	data->zone[nr].hyst = HYST_TO_REG(TEMP_FROM_REG(
		data->zone[nr].limit) - TEMP_FROM_REG(
		data->zone[nr].off_desired));
	if (nr == 0 || nr == 1) {
		lm85_write_value(client, LM85_REG_AFAN_HYST1,
			(data->zone[0].hyst << 4)
			| data->zone[1].hyst);
	} else {
		lm85_write_value(client, LM85_REG_AFAN_HYST2,
			(data->zone[2].hyst << 4));
	}
	mutex_unlock(&data->update_lock);
	return count;
}