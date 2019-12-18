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
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int DM646X_EVM_ATA_PWD ; 
 int DM646X_EVM_ATA_RST ; 
 scalar_t__ HAS_ATA ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int cpld_reg0_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	if (HAS_ATA) {
		u8 data;
		struct i2c_msg msg[2] = {
			{
				.addr = client->addr,
				.flags = I2C_M_RD,
				.len = 1,
				.buf = &data,
			},
			{
				.addr = client->addr,
				.flags = 0,
				.len = 1,
				.buf = &data,
			},
		};

		/* Clear ATA_RSTn and ATA_PWD bits to enable ATA operation. */
		i2c_transfer(client->adapter, msg, 1);
		data &= ~(DM646X_EVM_ATA_RST | DM646X_EVM_ATA_PWD);
		i2c_transfer(client->adapter, msg + 1, 1);
	}

	return 0;
}