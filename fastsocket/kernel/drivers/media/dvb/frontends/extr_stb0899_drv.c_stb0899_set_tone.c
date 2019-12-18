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
struct stb0899_internal {int master_clk; } ;
struct stb0899_state {struct stb0899_internal internal; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
typedef  int fe_sec_tone_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACRPRESC ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int /*<<< orphan*/  STB0899_ACRDIV1 ; 
 int /*<<< orphan*/  STB0899_ACRPRESC ; 
 int /*<<< orphan*/  STB0899_DISEQCOCFG ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stb0899_wait_diseqc_txidle (struct stb0899_state*,int) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stb0899_set_tone(struct dvb_frontend *fe, fe_sec_tone_mode_t tone)
{
	struct stb0899_state *state = fe->demodulator_priv;
	struct stb0899_internal *internal = &state->internal;

	u8 div, reg;

	/* wait for diseqc idle	*/
	if (stb0899_wait_diseqc_txidle(state, 100) < 0)
		return -ETIMEDOUT;

	switch (tone) {
	case SEC_TONE_ON:
		div = (internal->master_clk / 100) / 5632;
		div = (div + 5) / 10;
		stb0899_write_reg(state, STB0899_DISEQCOCFG, 0x66);
		reg = stb0899_read_reg(state, STB0899_ACRPRESC);
		STB0899_SETFIELD_VAL(ACRPRESC, reg, 0x03);
		stb0899_write_reg(state, STB0899_ACRPRESC, reg);
		stb0899_write_reg(state, STB0899_ACRDIV1, div);
		break;
	case SEC_TONE_OFF:
		stb0899_write_reg(state, STB0899_DISEQCOCFG, 0x20);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}