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
struct adm1025_data {int valid; int* in; int* in_min; int* in_max; int* temp; int* temp_min; int* temp_max; int alarms; int vid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1025_REG_IN (int) ; 
 int /*<<< orphan*/  ADM1025_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  ADM1025_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  ADM1025_REG_STATUS1 ; 
 int /*<<< orphan*/  ADM1025_REG_STATUS2 ; 
 int /*<<< orphan*/  ADM1025_REG_TEMP (int) ; 
 int /*<<< orphan*/  ADM1025_REG_TEMP_HIGH (int) ; 
 int /*<<< orphan*/  ADM1025_REG_TEMP_LOW (int) ; 
 int /*<<< orphan*/  ADM1025_REG_VID ; 
 int /*<<< orphan*/  ADM1025_REG_VID4 ; 
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct adm1025_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct adm1025_data *adm1025_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1025_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ * 2) || !data->valid) {
		int i;

		dev_dbg(&client->dev, "Updating data.\n");
		for (i=0; i<6; i++) {
			data->in[i] = i2c_smbus_read_byte_data(client,
				      ADM1025_REG_IN(i));
			data->in_min[i] = i2c_smbus_read_byte_data(client,
					  ADM1025_REG_IN_MIN(i));
			data->in_max[i] = i2c_smbus_read_byte_data(client,
					  ADM1025_REG_IN_MAX(i));
		}
		for (i=0; i<2; i++) {
			data->temp[i] = i2c_smbus_read_byte_data(client,
					ADM1025_REG_TEMP(i));
			data->temp_min[i] = i2c_smbus_read_byte_data(client,
					    ADM1025_REG_TEMP_LOW(i));
			data->temp_max[i] = i2c_smbus_read_byte_data(client,
					    ADM1025_REG_TEMP_HIGH(i));
		}
		data->alarms = i2c_smbus_read_byte_data(client,
			       ADM1025_REG_STATUS1)
			     | (i2c_smbus_read_byte_data(client,
				ADM1025_REG_STATUS2) << 8);
		data->vid = (i2c_smbus_read_byte_data(client,
			     ADM1025_REG_VID) & 0x0f)
			  | ((i2c_smbus_read_byte_data(client,
			      ADM1025_REG_VID4) & 0x01) << 4);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}