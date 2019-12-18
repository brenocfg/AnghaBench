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
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GL518_REG_CHIP_ID ; 
 int /*<<< orphan*/  GL518_REG_CONF ; 
 int /*<<< orphan*/  GL518_REG_REVISION ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gl518_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int gl518sm_r00 ; 
 int gl518sm_r80 ; 
 int /*<<< orphan*/  i2c_adapter_id (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gl518_detect(struct i2c_client *client, int kind,
			struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int i;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	/* Now, we do the remaining detection. */

	if (kind < 0) {
		if ((gl518_read_value(client, GL518_REG_CHIP_ID) != 0x80)
		 || (gl518_read_value(client, GL518_REG_CONF) & 0x80))
			return -ENODEV;
	}

	/* Determine the chip type. */
	if (kind <= 0) {
		i = gl518_read_value(client, GL518_REG_REVISION);
		if (i == 0x00) {
			kind = gl518sm_r00;
		} else if (i == 0x80) {
			kind = gl518sm_r80;
		} else {
			if (kind <= 0)
				dev_info(&adapter->dev,
				    "Ignoring 'force' parameter for unknown "
				    "chip at adapter %d, address 0x%02x\n",
				    i2c_adapter_id(adapter), client->addr);
			return -ENODEV;
		}
	}

	strlcpy(info->type, "gl518sm", I2C_NAME_SIZE);

	return 0;
}