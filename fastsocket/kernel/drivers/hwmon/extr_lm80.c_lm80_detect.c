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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  LM80_REG_ALARM2 ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int lm80_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm80_detect(struct i2c_client *client, int kind,
		       struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int i, cur;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Now, we do the remaining detection. It is lousy. */
	if (lm80_read_value(client, LM80_REG_ALARM2) & 0xc0)
		return -ENODEV;
	for (i = 0x2a; i <= 0x3d; i++) {
		cur = i2c_smbus_read_byte_data(client, i);
		if ((i2c_smbus_read_byte_data(client, i + 0x40) != cur)
		 || (i2c_smbus_read_byte_data(client, i + 0x80) != cur)
		 || (i2c_smbus_read_byte_data(client, i + 0xc0) != cur))
		    return -ENODEV;
	}

	strlcpy(info->type, "lm80", I2C_NAME_SIZE);

	return 0;
}