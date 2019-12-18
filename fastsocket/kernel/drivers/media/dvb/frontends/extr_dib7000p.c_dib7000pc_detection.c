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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

int dib7000pc_detection(struct i2c_adapter *i2c_adap)
{
	u8 tx[2], rx[2];
	struct i2c_msg msg[2] = {
		{ .addr = 18 >> 1, .flags = 0,        .buf = tx, .len = 2 },
		{ .addr = 18 >> 1, .flags = I2C_M_RD, .buf = rx, .len = 2 },
	};

	tx[0] = 0x03;
	tx[1] = 0x00;

	if (i2c_transfer(i2c_adap, msg, 2) == 2)
		if (rx[0] == 0x01 && rx[1] == 0xb3) {
			dprintk("-D-  DiB7000PC detected");
			return 1;
		}

	msg[0].addr = msg[1].addr = 0x40;

	if (i2c_transfer(i2c_adap, msg, 2) == 2)
		if (rx[0] == 0x01 && rx[1] == 0xb3) {
			dprintk("-D-  DiB7000PC detected");
			return 1;
		}

	dprintk("-D-  DiB7000PC not detected");
	return 0;
}