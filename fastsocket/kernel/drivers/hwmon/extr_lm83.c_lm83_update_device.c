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
struct lm83_data {int valid; int* temp; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__ alarms; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LM83_REG_R_STATUS1 ; 
 int /*<<< orphan*/  LM83_REG_R_STATUS2 ; 
 int /*<<< orphan*/ * LM83_REG_R_TEMP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lm83_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct lm83_data *lm83_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm83_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ * 2) || !data->valid) {
		int nr;

		dev_dbg(&client->dev, "Updating lm83 data.\n");
		for (nr = 0; nr < 9; nr++) {
			data->temp[nr] =
			    i2c_smbus_read_byte_data(client,
			    LM83_REG_R_TEMP[nr]);
		}
		data->alarms =
		    i2c_smbus_read_byte_data(client, LM83_REG_R_STATUS1)
		    + (i2c_smbus_read_byte_data(client, LM83_REG_R_STATUS2)
		    << 8);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}