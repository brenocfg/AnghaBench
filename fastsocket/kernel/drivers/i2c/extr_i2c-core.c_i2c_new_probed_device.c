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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
struct i2c_client {int dummy; } ;
struct i2c_board_info {unsigned short addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short const I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_QUICK ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BYTE ; 
 int /*<<< orphan*/  I2C_SMBUS_BYTE ; 
 int /*<<< orphan*/  I2C_SMBUS_QUICK ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int /*<<< orphan*/  I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned short const) ; 
 scalar_t__ i2c_check_addr (struct i2c_adapter*,unsigned short const) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 scalar_t__ i2c_smbus_xfer (struct i2c_adapter*,unsigned short const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 

struct i2c_client *
i2c_new_probed_device(struct i2c_adapter *adap,
		      struct i2c_board_info *info,
		      unsigned short const *addr_list)
{
	int i;

	/* Stop here if the bus doesn't support probing */
	if (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_BYTE)) {
		dev_err(&adap->dev, "Probing not supported\n");
		return NULL;
	}

	for (i = 0; addr_list[i] != I2C_CLIENT_END; i++) {
		/* Check address validity */
		if (addr_list[i] < 0x03 || addr_list[i] > 0x77) {
			dev_warn(&adap->dev, "Invalid 7-bit address "
				 "0x%02x\n", addr_list[i]);
			continue;
		}

		/* Check address availability */
		if (i2c_check_addr(adap, addr_list[i])) {
			dev_dbg(&adap->dev, "Address 0x%02x already in "
				"use, not probing\n", addr_list[i]);
			continue;
		}

		/* Test address responsiveness
		   The default probe method is a quick write, but it is known
		   to corrupt the 24RF08 EEPROMs due to a state machine bug,
		   and could also irreversibly write-protect some EEPROMs, so
		   for address ranges 0x30-0x37 and 0x50-0x5f, we use a byte
		   read instead. Also, some bus drivers don't implement
		   quick write, so we fallback to a byte read it that case
		   too. */
		if ((addr_list[i] & ~0x07) == 0x30
		 || (addr_list[i] & ~0x0f) == 0x50
		 || !i2c_check_functionality(adap, I2C_FUNC_SMBUS_QUICK)) {
			union i2c_smbus_data data;

			if (i2c_smbus_xfer(adap, addr_list[i], 0,
					   I2C_SMBUS_READ, 0,
					   I2C_SMBUS_BYTE, &data) >= 0)
				break;
		} else {
			if (i2c_smbus_xfer(adap, addr_list[i], 0,
					   I2C_SMBUS_WRITE, 0,
					   I2C_SMBUS_QUICK, NULL) >= 0)
				break;
		}
	}

	if (addr_list[i] == I2C_CLIENT_END) {
		dev_dbg(&adap->dev, "Probing failed, no device found\n");
		return NULL;
	}

	info->addr = addr_list[i];
	return i2c_new_device(adap, info);
}