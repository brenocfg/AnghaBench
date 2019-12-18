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
struct lm92_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* temp1_max; void* temp1_min; void* temp1_crit; void* temp1_hyst; void* temp1_input; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  LM92_REG_TEMP ; 
 int /*<<< orphan*/  LM92_REG_TEMP_CRIT ; 
 int /*<<< orphan*/  LM92_REG_TEMP_HIGH ; 
 int /*<<< orphan*/  LM92_REG_TEMP_HYST ; 
 int /*<<< orphan*/  LM92_REG_TEMP_LOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lm92_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* swab16 (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct lm92_data *lm92_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm92_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ)
	 || !data->valid) {
		dev_dbg(&client->dev, "Updating lm92 data\n");
		data->temp1_input = swab16(i2c_smbus_read_word_data(client,
				    LM92_REG_TEMP));
		data->temp1_hyst = swab16(i2c_smbus_read_word_data(client,
				    LM92_REG_TEMP_HYST));
		data->temp1_crit = swab16(i2c_smbus_read_word_data(client,
				    LM92_REG_TEMP_CRIT));
		data->temp1_min = swab16(i2c_smbus_read_word_data(client,
				    LM92_REG_TEMP_LOW));
		data->temp1_max = swab16(i2c_smbus_read_word_data(client,
				    LM92_REG_TEMP_HIGH));

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}