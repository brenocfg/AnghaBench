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
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1025_REG_CHIP_ID ; 
 int /*<<< orphan*/  ADM1025_REG_CONFIG ; 
 int /*<<< orphan*/  ADM1025_REG_MAN_ID ; 
 int /*<<< orphan*/  ADM1025_REG_STATUS1 ; 
 int /*<<< orphan*/  ADM1025_REG_STATUS2 ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int adm1025 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int ne1619 ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm1025_detect(struct i2c_client *client, int kind,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	const char *name = "";
	u8 config;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/*
	 * Now we do the remaining detection. A negative kind means that
	 * the driver was loaded with no force parameter (default), so we
	 * must both detect and identify the chip. A zero kind means that
	 * the driver was loaded with the force parameter, the detection
	 * step shall be skipped. A positive kind means that the driver
	 * was loaded with the force parameter and a given kind of chip is
	 * requested, so both the detection and the identification steps
	 * are skipped.
	 */
	config = i2c_smbus_read_byte_data(client, ADM1025_REG_CONFIG);
	if (kind < 0) { /* detection */
		if ((config & 0x80) != 0x00
		 || (i2c_smbus_read_byte_data(client,
		     ADM1025_REG_STATUS1) & 0xC0) != 0x00
		 || (i2c_smbus_read_byte_data(client,
		     ADM1025_REG_STATUS2) & 0xBC) != 0x00) {
			dev_dbg(&adapter->dev,
				"ADM1025 detection failed at 0x%02x.\n",
				client->addr);
			return -ENODEV;
		}
	}

	if (kind <= 0) { /* identification */
		u8 man_id, chip_id;

		man_id = i2c_smbus_read_byte_data(client, ADM1025_REG_MAN_ID);
		chip_id = i2c_smbus_read_byte_data(client, ADM1025_REG_CHIP_ID);

		if (man_id == 0x41) { /* Analog Devices */
			if ((chip_id & 0xF0) == 0x20) { /* ADM1025/ADM1025A */
				kind = adm1025;
			}
		} else
		if (man_id == 0xA1) { /* Philips */
			if (client->addr != 0x2E
			 && (chip_id & 0xF0) == 0x20) { /* NE1619 */
				kind = ne1619;
			}
		}

		if (kind <= 0) { /* identification failed */
			dev_info(&adapter->dev,
			    "Unsupported chip (man_id=0x%02X, "
			    "chip_id=0x%02X).\n", man_id, chip_id);
			return -ENODEV;
		}
	}

	if (kind == adm1025) {
		name = "adm1025";
	} else if (kind == ne1619) {
		name = "ne1619";
	}
	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}