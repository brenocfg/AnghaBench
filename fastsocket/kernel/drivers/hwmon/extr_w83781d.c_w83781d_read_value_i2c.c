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
typedef  int u16 ;
struct w83781d_data {struct i2c_client** lm75; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83781D_REG_BANK ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_smbus_read_word_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
w83781d_read_value_i2c(struct w83781d_data *data, u16 reg)
{
	struct i2c_client *client = data->client;
	int res, bank;
	struct i2c_client *cl;

	bank = (reg >> 8) & 0x0f;
	if (bank > 2)
		/* switch banks */
		i2c_smbus_write_byte_data(client, W83781D_REG_BANK,
					  bank);
	if (bank == 0 || bank > 2) {
		res = i2c_smbus_read_byte_data(client, reg & 0xff);
	} else {
		/* switch to subclient */
		cl = data->lm75[bank - 1];
		/* convert from ISA to LM75 I2C addresses */
		switch (reg & 0xff) {
		case 0x50:	/* TEMP */
			res = swab16(i2c_smbus_read_word_data(cl, 0));
			break;
		case 0x52:	/* CONFIG */
			res = i2c_smbus_read_byte_data(cl, 1);
			break;
		case 0x53:	/* HYST */
			res = swab16(i2c_smbus_read_word_data(cl, 2));
			break;
		case 0x55:	/* OVER */
		default:
			res = swab16(i2c_smbus_read_word_data(cl, 3));
			break;
		}
	}
	if (bank > 2)
		i2c_smbus_write_byte_data(client, W83781D_REG_BANK, 0);

	return res;
}