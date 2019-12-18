#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tda1004x_state {int /*<<< orphan*/  i2c; TYPE_2__* config; } ;
struct saa7134_dev {int dummy; } ;
struct i2c_msg {int addr; int len; int* buf; int /*<<< orphan*/  flags; } ;
struct dvb_frontend {TYPE_1__* dvb; struct tda1004x_state* demodulator_priv; } ;
struct TYPE_4__ {int i2c_gate; } ;
struct TYPE_3__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  wprintk (char*) ; 

__attribute__((used)) static int tda8290_i2c_gate_ctrl( struct dvb_frontend* fe, int enable)
{
	struct tda1004x_state *state = fe->demodulator_priv;

	u8 addr = state->config->i2c_gate;
	static u8 tda8290_close[] = { 0x21, 0xc0};
	static u8 tda8290_open[]  = { 0x21, 0x80};
	struct i2c_msg tda8290_msg = {.addr = addr,.flags = 0, .len = 2};
	if (enable) {
		tda8290_msg.buf = tda8290_close;
	} else {
		tda8290_msg.buf = tda8290_open;
	}
	if (i2c_transfer(state->i2c, &tda8290_msg, 1) != 1) {
		struct saa7134_dev *dev = fe->dvb->priv;
		wprintk("could not access tda8290 I2C gate\n");
		return -EIO;
	}
	msleep(20);
	return 0;
}