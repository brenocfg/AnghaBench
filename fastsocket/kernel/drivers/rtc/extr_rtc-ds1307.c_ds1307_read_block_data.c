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
typedef  scalar_t__ u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int BLOCK_DATA_MAX_TRIES ; 
 scalar_t__ EIO ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ds1307_read_block_data_once (struct i2c_client*,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static s32 ds1307_read_block_data(struct i2c_client *client, u8 command,
				  u8 length, u8 *values)
{
	u8 oldvalues[I2C_SMBUS_BLOCK_MAX];
	s32 ret;
	int tries = 0;

	dev_dbg(&client->dev, "ds1307_read_block_data (length=%d)\n", length);
	ret = ds1307_read_block_data_once(client, command, length, values);
	if (ret < 0)
		return ret;
	do {
		if (++tries > BLOCK_DATA_MAX_TRIES) {
			dev_err(&client->dev,
				"ds1307_read_block_data failed\n");
			return -EIO;
		}
		memcpy(oldvalues, values, length);
		ret = ds1307_read_block_data_once(client, command, length,
						  values);
		if (ret < 0)
			return ret;
	} while (memcmp(oldvalues, values, length));
	return length;
}