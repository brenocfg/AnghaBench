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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  F75375_CHIP_ID ; 
 int /*<<< orphan*/  F75375_REG_VENDOR ; 
 int /*<<< orphan*/  F75375_REG_VERSION ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int f75373 ; 
 int f75375 ; 
 int f75375_read16 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f75375_read8 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f75375_detect(struct i2c_client *client, int kind,
			 struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	u8 version = 0;
	const char *name = "";

	if (kind < 0) {
		u16 vendid = f75375_read16(client, F75375_REG_VENDOR);
		u16 chipid = f75375_read16(client, F75375_CHIP_ID);
		version = f75375_read8(client, F75375_REG_VERSION);
		if (chipid == 0x0306 && vendid == 0x1934) {
			kind = f75375;
		} else if (chipid == 0x0204 && vendid == 0x1934) {
			kind = f75373;
		} else {
			dev_err(&adapter->dev,
				"failed,%02X,%02X,%02X\n",
				chipid, version, vendid);
			return -ENODEV;
		}
	}

	if (kind == f75375) {
		name = "f75375";
	} else if (kind == f75373) {
		name = "f75373";
	}
	dev_info(&adapter->dev, "found %s version: %02X\n", name, version);
	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}