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
struct max1619_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* alarms; void* temp_hyst2; void* temp_crit2; void* temp_low2; void* temp_high2; void* temp_input2; void* temp_input1; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MAX1619_REG_R_LOCAL_TEMP ; 
 int /*<<< orphan*/  MAX1619_REG_R_REMOTE_CRIT ; 
 int /*<<< orphan*/  MAX1619_REG_R_REMOTE_HIGH ; 
 int /*<<< orphan*/  MAX1619_REG_R_REMOTE_LOW ; 
 int /*<<< orphan*/  MAX1619_REG_R_REMOTE_TEMP ; 
 int /*<<< orphan*/  MAX1619_REG_R_STATUS ; 
 int /*<<< orphan*/  MAX1619_REG_R_TCRIT_HYST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct max1619_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct max1619_data *max1619_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct max1619_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ * 2) || !data->valid) {
		dev_dbg(&client->dev, "Updating max1619 data.\n");
		data->temp_input1 = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_LOCAL_TEMP);
		data->temp_input2 = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_REMOTE_TEMP);
		data->temp_high2 = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_REMOTE_HIGH);
		data->temp_low2 = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_REMOTE_LOW);
		data->temp_crit2 = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_REMOTE_CRIT);
		data->temp_hyst2 = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_TCRIT_HYST);
		data->alarms = i2c_smbus_read_byte_data(client,
					MAX1619_REG_R_STATUS);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}