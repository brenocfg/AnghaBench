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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  warn (char*,int,int) ; 

__attribute__((used)) static int af9013_write_regs(struct af9013_state *state, u8 mbox, u16 reg,
	u8 *val, u8 len)
{
	u8 buf[3+len];
	struct i2c_msg msg = {
		.addr = state->config.demod_address,
		.flags = 0,
		.len = sizeof(buf),
		.buf = buf };

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	buf[2] = mbox;
	memcpy(&buf[3], val, len);

	if (i2c_transfer(state->i2c, &msg, 1) != 1) {
		warn("I2C write failed reg:%04x len:%d", reg, len);
		return -EREMOTEIO;
	}
	return 0;
}