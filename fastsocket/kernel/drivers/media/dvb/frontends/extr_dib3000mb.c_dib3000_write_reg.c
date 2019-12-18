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
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;
struct dib3000_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  deb_i2c (char*,int,int,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int dib3000_write_reg(struct dib3000_state *state, u16 reg, u16 val)
{
	u8 b[] = {
		(reg >> 8) & 0xff, reg & 0xff,
		(val >> 8) & 0xff, val & 0xff,
	};
	struct i2c_msg msg[] = {
		{ .addr = state->config.demod_address, .flags = 0, .buf = b, .len = 4 }
	};
	deb_i2c("writing i2c bus (reg: %5d 0x%04x, val: %5d 0x%04x)\n",reg,reg,val,val);

	return i2c_transfer(state->i2c,msg, 1) != 1 ? -EREMOTEIO : 0;
}