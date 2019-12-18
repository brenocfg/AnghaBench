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
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;
struct mt352_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {struct mt352_state* demodulator_priv; } ;

/* Variables and functions */
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt352_single_write(struct dvb_frontend *fe, u8 reg, u8 val)
{
	struct mt352_state* state = fe->demodulator_priv;
	u8 buf[2] = { reg, val };
	struct i2c_msg msg = { .addr = state->config.demod_address, .flags = 0,
			       .buf = buf, .len = 2 };
	int err = i2c_transfer(state->i2c, &msg, 1);
	if (err != 1) {
		printk("mt352_write() to reg %x failed (err = %d)!\n", reg, err);
		return err;
	}
	return 0;
}