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
union i2c_smbus_data {int byte; int word; } ;
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct stub_chip {size_t pointer; int* words; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_QUICK 129 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int MAX_CHIPS ; 
 scalar_t__* chip_addr ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct stub_chip* stub_chips ; 

__attribute__((used)) static s32 stub_xfer(struct i2c_adapter * adap, u16 addr, unsigned short flags,
	char read_write, u8 command, int size, union i2c_smbus_data * data)
{
	s32 ret;
	int i;
	struct stub_chip *chip = NULL;

	/* Search for the right chip */
	for (i = 0; i < MAX_CHIPS && chip_addr[i]; i++) {
		if (addr == chip_addr[i]) {
			chip = stub_chips + i;
			break;
		}
	}
	if (!chip)
		return -ENODEV;

	switch (size) {

	case I2C_SMBUS_QUICK:
		dev_dbg(&adap->dev, "smbus quick - addr 0x%02x\n", addr);
		ret = 0;
		break;

	case I2C_SMBUS_BYTE:
		if (read_write == I2C_SMBUS_WRITE) {
			chip->pointer = command;
			dev_dbg(&adap->dev, "smbus byte - addr 0x%02x, "
					"wrote 0x%02x.\n",
					addr, command);
		} else {
			data->byte = chip->words[chip->pointer++] & 0xff;
			dev_dbg(&adap->dev, "smbus byte - addr 0x%02x, "
					"read  0x%02x.\n",
					addr, data->byte);
		}

		ret = 0;
		break;

	case I2C_SMBUS_BYTE_DATA:
		if (read_write == I2C_SMBUS_WRITE) {
			chip->words[command] &= 0xff00;
			chip->words[command] |= data->byte;
			dev_dbg(&adap->dev, "smbus byte data - addr 0x%02x, "
					"wrote 0x%02x at 0x%02x.\n",
					addr, data->byte, command);
		} else {
			data->byte = chip->words[command] & 0xff;
			dev_dbg(&adap->dev, "smbus byte data - addr 0x%02x, "
					"read  0x%02x at 0x%02x.\n",
					addr, data->byte, command);
		}
		chip->pointer = command + 1;

		ret = 0;
		break;

	case I2C_SMBUS_WORD_DATA:
		if (read_write == I2C_SMBUS_WRITE) {
			chip->words[command] = data->word;
			dev_dbg(&adap->dev, "smbus word data - addr 0x%02x, "
					"wrote 0x%04x at 0x%02x.\n",
					addr, data->word, command);
		} else {
			data->word = chip->words[command];
			dev_dbg(&adap->dev, "smbus word data - addr 0x%02x, "
					"read  0x%04x at 0x%02x.\n",
					addr, data->word, command);
		}

		ret = 0;
		break;

	default:
		dev_dbg(&adap->dev, "Unsupported I2C/SMBus command\n");
		ret = -EOPNOTSUPP;
		break;
	} /* switch (size) */

	return ret;
}