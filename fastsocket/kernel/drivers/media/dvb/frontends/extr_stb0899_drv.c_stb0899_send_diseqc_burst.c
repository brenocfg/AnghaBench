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
struct stb0899_state {int dummy; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
typedef  int fe_sec_mini_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQCMODE ; 
 int /*<<< orphan*/  DISPRECHARGE ; 
 int ETIMEDOUT ; 
#define  SEC_MINI_A 129 
#define  SEC_MINI_B 128 
 int /*<<< orphan*/  STB0899_DISCNTRL1 ; 
 int /*<<< orphan*/  STB0899_DISFIFO ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stb0899_wait_diseqc_txidle (struct stb0899_state*,int) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stb0899_send_diseqc_burst(struct dvb_frontend *fe, fe_sec_mini_cmd_t burst)
{
	struct stb0899_state *state = fe->demodulator_priv;
	u8 reg, old_state;

	/* wait for diseqc idle	*/
	if (stb0899_wait_diseqc_txidle(state, 100) < 0)
		return -ETIMEDOUT;

	reg = stb0899_read_reg(state, STB0899_DISCNTRL1);
	old_state = reg;
	/* set to burst mode	*/
	STB0899_SETFIELD_VAL(DISEQCMODE, reg, 0x03);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 0x01);
	stb0899_write_reg(state, STB0899_DISCNTRL1, reg);
	switch (burst) {
	case SEC_MINI_A:
		/* unmodulated	*/
		stb0899_write_reg(state, STB0899_DISFIFO, 0x00);
		break;
	case SEC_MINI_B:
		/* modulated	*/
		stb0899_write_reg(state, STB0899_DISFIFO, 0xff);
		break;
	}
	reg = stb0899_read_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 0x00);
	stb0899_write_reg(state, STB0899_DISCNTRL1, reg);
	/* wait for diseqc idle	*/
	if (stb0899_wait_diseqc_txidle(state, 100) < 0)
		return -ETIMEDOUT;

	/* restore state	*/
	stb0899_write_reg(state, STB0899_DISCNTRL1, old_state);

	return 0;
}