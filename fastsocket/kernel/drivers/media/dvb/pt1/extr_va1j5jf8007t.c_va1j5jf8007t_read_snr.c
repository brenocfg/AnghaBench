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
typedef  int /*<<< orphan*/  write_buf ;
typedef  int u8 ;
typedef  int u16 ;
struct va1j5jf8007t_state {int /*<<< orphan*/  adap; TYPE_1__* config; } ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct dvb_frontend {struct va1j5jf8007t_state* demodulator_priv; } ;
typedef  int s64 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  read_buf ;
struct TYPE_2__ {int demod_address; } ;

/* Variables and functions */
 int EIO ; 
 int EREMOTEIO ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int intlog10 (int) ; 

__attribute__((used)) static int va1j5jf8007t_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct va1j5jf8007t_state *state;
	u8 addr;
	int i;
	u8 write_buf[1], read_buf[1];
	struct i2c_msg msgs[2];
	s32 word, x, y;

	state = fe->demodulator_priv;
	addr = state->config->demod_address;

	word = 0;
	for (i = 0; i < 3; i++) {
		write_buf[0] = 0x8b + i;

		msgs[0].addr = addr;
		msgs[0].flags = 0;
		msgs[0].len = sizeof(write_buf);
		msgs[0].buf = write_buf;

		msgs[1].addr = addr;
		msgs[1].flags = I2C_M_RD;
		msgs[1].len = sizeof(read_buf);
		msgs[1].buf = read_buf;

		if (i2c_transfer(state->adap, msgs, 2) != 2)
			return -EREMOTEIO;

		word <<= 8;
		word |= read_buf[0];
	}

	if (!word)
		return -EIO;

	x = 10 * (intlog10(0x540000 * 100 / word) - (2 << 24));
	y = (24ll << 46) / 1000000;
	y = ((s64)y * x >> 30) - (16ll << 40) / 10000;
	y = ((s64)y * x >> 29) + (398ll << 35) / 10000;
	y = ((s64)y * x >> 30) + (5491ll << 29) / 10000;
	y = ((s64)y * x >> 30) + (30965ll << 23) / 10000;
	*snr = y >> 15;
	return 0;
}