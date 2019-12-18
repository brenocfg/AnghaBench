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
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GL520_REG_CHIP_ID ; 
 int /*<<< orphan*/  GL520_REG_CONF ; 
 int /*<<< orphan*/  GL520_REG_REVISION ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gl520_detect(struct i2c_client *client, int kind,
			struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	/* Determine the chip type. */
	if (kind < 0) {
		if ((gl520_read_value(client, GL520_REG_CHIP_ID) != 0x20) ||
		    ((gl520_read_value(client, GL520_REG_REVISION) & 0x7f) != 0x00) ||
		    ((gl520_read_value(client, GL520_REG_CONF) & 0x80) != 0x00)) {
			dev_dbg(&client->dev, "Unknown chip type, skipping\n");
			return -ENODEV;
		}
	}

	strlcpy(info->type, "gl520sm", I2C_NAME_SIZE);

	return 0;
}