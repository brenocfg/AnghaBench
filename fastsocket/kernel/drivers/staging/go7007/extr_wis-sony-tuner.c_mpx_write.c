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
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPX_I2C_ADDR ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int mpx_write(struct i2c_client *client, int dev, int addr, int val)
{
	u8 buffer[5];
	struct i2c_msg msg;

	buffer[0] = dev;
	buffer[1] = addr >> 8;
	buffer[2] = addr & 0xff;
	buffer[3] = val >> 8;
	buffer[4] = val & 0xff;
	msg.addr = MPX_I2C_ADDR;
	msg.flags = 0;
	msg.len = 5;
	msg.buf = buffer;
	i2c_transfer(client->adapter, &msg, 1);
	return 0;
}