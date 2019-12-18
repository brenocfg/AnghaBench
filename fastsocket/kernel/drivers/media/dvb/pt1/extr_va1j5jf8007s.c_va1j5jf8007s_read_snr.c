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
struct va1j5jf8007s_state {int /*<<< orphan*/  adap; TYPE_1__* config; } ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct dvb_frontend {struct va1j5jf8007s_state* demodulator_priv; } ;
typedef  int s64 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  read_buf ;
struct TYPE_2__ {int demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 long long int_sqrt (int) ; 

__attribute__((used)) static int va1j5jf8007s_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct va1j5jf8007s_state *state;
	u8 addr;
	int i;
	u8 write_buf[1], read_buf[1];
	struct i2c_msg msgs[2];
	s32 word, x1, x2, x3, x4, x5, y;

	state = fe->demodulator_priv;
	addr = state->config->demod_address;

	word = 0;
	for (i = 0; i < 2; i++) {
		write_buf[0] = 0xbc + i;

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

	word -= 3000;
	if (word < 0)
		word = 0;

	x1 = int_sqrt(word << 16) * ((15625ll << 21) / 1000000);
	x2 = (s64)x1 * x1 >> 31;
	x3 = (s64)x2 * x1 >> 31;
	x4 = (s64)x2 * x2 >> 31;
	x5 = (s64)x4 * x1 >> 31;

	y = (58857ll << 23) / 1000;
	y -= (s64)x1 * ((89565ll << 24) / 1000) >> 30;
	y += (s64)x2 * ((88977ll << 24) / 1000) >> 28;
	y -= (s64)x3 * ((50259ll << 25) / 1000) >> 27;
	y += (s64)x4 * ((14341ll << 27) / 1000) >> 27;
	y -= (s64)x5 * ((16346ll << 30) / 10000) >> 28;

	*snr = y < 0 ? 0 : y >> 15;
	return 0;
}