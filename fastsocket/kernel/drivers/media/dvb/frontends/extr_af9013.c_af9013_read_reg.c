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
typedef  int u16 ;
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;
struct af9013_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  ibuf ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int af9013_read_reg(struct af9013_state *state, u16 reg, u8 *val)
{
	u8 obuf[3] = { reg >> 8, reg & 0xff, 0 };
	u8 ibuf[1];
	struct i2c_msg msg[2] = {
		{
			.addr = state->config.demod_address,
			.flags = 0,
			.len = sizeof(obuf),
			.buf = obuf
		}, {
			.addr = state->config.demod_address,
			.flags = I2C_M_RD,
			.len = sizeof(ibuf),
			.buf = ibuf
		}
	};

	if (i2c_transfer(state->i2c, msg, 2) != 2) {
		warn("I2C read failed reg:%04x", reg);
		return -EREMOTEIO;
	}
	*val = ibuf[0];
	return 0;
}