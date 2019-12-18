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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  TMP401_CONFIG_READ ; 
 int /*<<< orphan*/  TMP401_CONVERSION_RATE_READ ; 
#define  TMP401_DEVICE_ID 129 
 int /*<<< orphan*/  TMP401_DEVICE_ID_REG ; 
 int TMP401_MANUFACTURER_ID ; 
 int /*<<< orphan*/  TMP401_MANUFACTURER_ID_REG ; 
#define  TMP411_DEVICE_ID 128 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tmp401 ; 
 TYPE_1__* tmp401_id ; 
 int tmp411 ; 

__attribute__((used)) static int tmp401_detect(struct i2c_client *client, int kind,
			 struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detect and identify the chip */
	if (kind <= 0) {
		u8 reg;

		reg = i2c_smbus_read_byte_data(client,
					       TMP401_MANUFACTURER_ID_REG);
		if (reg != TMP401_MANUFACTURER_ID)
			return -ENODEV;

		reg = i2c_smbus_read_byte_data(client, TMP401_DEVICE_ID_REG);

		switch (reg) {
		case TMP401_DEVICE_ID:
			kind = tmp401;
			break;
		case TMP411_DEVICE_ID:
			kind = tmp411;
			break;
		default:
			return -ENODEV;
		}

		reg = i2c_smbus_read_byte_data(client, TMP401_CONFIG_READ);
		if (reg & 0x1b)
			return -ENODEV;

		reg = i2c_smbus_read_byte_data(client,
					       TMP401_CONVERSION_RATE_READ);
		/* Datasheet says: 0x1-0x6 */
		if (reg > 15)
			return -ENODEV;
	}
	strlcpy(info->type, tmp401_id[kind - 1].name, I2C_NAME_SIZE);

	return 0;
}