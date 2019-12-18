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
struct lgdt3305_state {TYPE_1__* cfg; int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  lg_err (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lg_reg (char*,int) ; 

__attribute__((used)) static int lgdt3305_read_reg(struct lgdt3305_state *state, u16 reg, u8 *val)
{
	int ret;
	u8 reg_buf[] = { reg >> 8, reg & 0xff };
	struct i2c_msg msg[] = {
		{ .addr = state->cfg->i2c_addr,
		  .flags = 0, .buf = reg_buf, .len = 2 },
		{ .addr = state->cfg->i2c_addr,
		  .flags = I2C_M_RD, .buf = val, .len = 1 },
	};

	lg_reg("reg: 0x%04x\n", reg);

	ret = i2c_transfer(state->i2c_adap, msg, 2);

	if (ret != 2) {
		lg_err("error (addr %02x reg %04x error (ret == %i)\n",
		       state->cfg->i2c_addr, reg, ret);
		if (ret < 0)
			return ret;
		else
			return -EREMOTEIO;
	}
	return 0;
}