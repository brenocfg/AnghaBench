#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
#define  TMP421_DEVICE_ID 130 
 int /*<<< orphan*/  TMP421_DEVICE_ID_REG ; 
 int TMP421_MANUFACTURER_ID ; 
 int /*<<< orphan*/  TMP421_MANUFACTURER_ID_REG ; 
#define  TMP422_DEVICE_ID 129 
#define  TMP423_DEVICE_ID 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tmp421 ; 
 TYPE_1__* tmp421_id ; 
 int tmp422 ; 
 int tmp423 ; 

__attribute__((used)) static int tmp421_detect(struct i2c_client *client, int kind,
			 struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	const char *names[] = { "TMP421", "TMP422", "TMP423" };

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	if (kind <= 0) {
		u8 reg;

		reg = i2c_smbus_read_byte_data(client,
					       TMP421_MANUFACTURER_ID_REG);
		if (reg != TMP421_MANUFACTURER_ID)
			return -ENODEV;

		reg = i2c_smbus_read_byte_data(client,
					       TMP421_DEVICE_ID_REG);
		switch (reg) {
		case TMP421_DEVICE_ID:
			kind = tmp421;
			break;
		case TMP422_DEVICE_ID:
			kind = tmp422;
			break;
		case TMP423_DEVICE_ID:
			kind = tmp423;
			break;
		default:
			return -ENODEV;
		}
	}
	strlcpy(info->type, tmp421_id[kind - 1].name, I2C_NAME_SIZE);
	dev_info(&adapter->dev, "Detected TI %s chip at 0x%02x\n",
		 names[kind - 1], client->addr);

	return 0;
}