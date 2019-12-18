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
union i2c_smbus_data {int /*<<< orphan*/  byte; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int dummy; } ;
struct go7007 {int dummy; } ;

/* Variables and functions */
 unsigned short I2C_CLIENT_SCCB ; 
 int I2C_SMBUS_BYTE_DATA ; 
 char I2C_SMBUS_READ ; 
 int go7007_i2c_xfer (struct go7007*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct go7007* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int go7007_smbus_xfer(struct i2c_adapter *adapter, u16 addr,
		unsigned short flags, char read_write,
		u8 command, int size, union i2c_smbus_data *data)
{
	struct go7007 *go = i2c_get_adapdata(adapter);

	if (size != I2C_SMBUS_BYTE_DATA)
		return -1;
	return go7007_i2c_xfer(go, addr, read_write == I2C_SMBUS_READ, command,
			flags & I2C_CLIENT_SCCB ? 0x10 : 0x00, &data->byte);
}