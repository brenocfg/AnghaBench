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
struct tmp401_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* temp_crit_hyst; void* config; void* status; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  TMP401_CONFIG_READ ; 
 int /*<<< orphan*/  TMP401_STATUS ; 
 int /*<<< orphan*/  TMP401_TEMP_CRIT_HYST ; 
 struct tmp401_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tmp401_update_device_reg16 (struct i2c_client*,struct tmp401_data*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct tmp401_data *tmp401_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct tmp401_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		data->status = i2c_smbus_read_byte_data(client, TMP401_STATUS);
		data->config = i2c_smbus_read_byte_data(client,
						TMP401_CONFIG_READ);
		tmp401_update_device_reg16(client, data);

		data->temp_crit_hyst = i2c_smbus_read_byte_data(client,
						TMP401_TEMP_CRIT_HYST);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}