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
typedef  int u8 ;
struct smsc47m192_data {int valid; int* in; int* in_min; int* in_max; int* temp; int* temp_max; int* temp_min; int* temp_offset; int vid; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SMSC47M192_REG_ALARM1 ; 
 int /*<<< orphan*/  SMSC47M192_REG_ALARM2 ; 
 int /*<<< orphan*/  SMSC47M192_REG_CONFIG ; 
 int /*<<< orphan*/  SMSC47M192_REG_IN (int) ; 
 int /*<<< orphan*/  SMSC47M192_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  SMSC47M192_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  SMSC47M192_REG_SFR ; 
 int /*<<< orphan*/ * SMSC47M192_REG_TEMP ; 
 int /*<<< orphan*/ * SMSC47M192_REG_TEMP_MAX ; 
 int /*<<< orphan*/ * SMSC47M192_REG_TEMP_MIN ; 
 int /*<<< orphan*/  SMSC47M192_REG_TEMP_OFFSET (int) ; 
 int /*<<< orphan*/  SMSC47M192_REG_VID ; 
 int /*<<< orphan*/  SMSC47M192_REG_VID4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct smsc47m192_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct smsc47m192_data *smsc47m192_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct smsc47m192_data *data = i2c_get_clientdata(client);
	int i, config;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	 || !data->valid) {
		u8 sfr = i2c_smbus_read_byte_data(client, SMSC47M192_REG_SFR);

		dev_dbg(&client->dev, "Starting smsc47m192 update\n");

		for (i = 0; i <= 7; i++) {
			data->in[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_IN(i));
			data->in_min[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_IN_MIN(i));
			data->in_max[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_IN_MAX(i));
		}
		for (i = 0; i < 3; i++) {
			data->temp[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_TEMP[i]);
			data->temp_max[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_TEMP_MAX[i]);
			data->temp_min[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_TEMP_MIN[i]);
		}
		for (i = 1; i < 3; i++)
			data->temp_offset[i] = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_TEMP_OFFSET(i));
		/* first offset is temp_offset[0] if SFR bit 4 is set,
					temp_offset[1] otherwise */
		if (sfr & 0x10) {
			data->temp_offset[0] = data->temp_offset[1];
			data->temp_offset[1] = 0;
		} else
			data->temp_offset[0] = 0;

		data->vid = i2c_smbus_read_byte_data(client, SMSC47M192_REG_VID)
			    & 0x0f;
		config = i2c_smbus_read_byte_data(client,
						  SMSC47M192_REG_CONFIG);
		if (config & 0x20)
			data->vid |= (i2c_smbus_read_byte_data(client,
					SMSC47M192_REG_VID4) & 0x01) << 4;
		data->alarms = i2c_smbus_read_byte_data(client,
						SMSC47M192_REG_ALARM1) |
			       (i2c_smbus_read_byte_data(client,
		       				SMSC47M192_REG_ALARM2) << 8);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}