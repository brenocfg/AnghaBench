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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;
struct ec100_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec100_write_reg(struct ec100_state *state, u8 reg, u8 val)
{
	u8 buf[2] = {reg, val};
	struct i2c_msg msg = {
		.addr = state->config.demod_address,
		.flags = 0,
		.len = 2,
		.buf = buf};

	if (i2c_transfer(state->i2c, &msg, 1) != 1) {
		warn("I2C write failed reg:%02x", reg);
		return -EREMOTEIO;
	}
	return 0;
}