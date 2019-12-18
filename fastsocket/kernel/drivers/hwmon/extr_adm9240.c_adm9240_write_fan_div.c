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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM9240_REG_VID_FAN_DIV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adm9240_write_fan_div(struct i2c_client *client, int nr,
		u8 fan_div)
{
	u8 reg, old, shift = (nr + 2) * 2;

	reg = i2c_smbus_read_byte_data(client, ADM9240_REG_VID_FAN_DIV);
	old = (reg >> shift) & 3;
	reg &= ~(3 << shift);
	reg |= (fan_div << shift);
	i2c_smbus_write_byte_data(client, ADM9240_REG_VID_FAN_DIV, reg);
	dev_dbg(&client->dev, "fan%d clock divider changed from %u "
			"to %u\n", nr + 1, 1 << old, 1 << fan_div);
}