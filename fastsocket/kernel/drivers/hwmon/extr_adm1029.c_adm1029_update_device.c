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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct adm1029_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void** fan_div; void** fan; void** temp; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ADM1029_REG_FAN ; 
 int /*<<< orphan*/ * ADM1029_REG_FAN_DIV ; 
 int /*<<< orphan*/ * ADM1029_REG_TEMP ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct adm1029_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct adm1029_data *adm1029_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1029_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);
	/*
	 * Use the "cache" Luke, don't recheck values
	 * if there are already checked not a long time later
	 */
	if (time_after(jiffies, data->last_updated + HZ * 2)
	 || !data->valid) {
		int nr;

		dev_dbg(&client->dev, "Updating adm1029 data\n");

		for (nr = 0; nr < ARRAY_SIZE(ADM1029_REG_TEMP); nr++) {
			data->temp[nr] =
			    i2c_smbus_read_byte_data(client,
						     ADM1029_REG_TEMP[nr]);
		}
		for (nr = 0; nr < ARRAY_SIZE(ADM1029_REG_FAN); nr++) {
			data->fan[nr] =
			    i2c_smbus_read_byte_data(client,
						     ADM1029_REG_FAN[nr]);
		}
		for (nr = 0; nr < ARRAY_SIZE(ADM1029_REG_FAN_DIV); nr++) {
			data->fan_div[nr] =
			    i2c_smbus_read_byte_data(client,
						     ADM1029_REG_FAN_DIV[nr]);
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}