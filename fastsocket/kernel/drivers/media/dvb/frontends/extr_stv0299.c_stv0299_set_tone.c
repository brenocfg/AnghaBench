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
struct stv0299_state {int dummy; } ;
struct dvb_frontend {struct stv0299_state* demodulator_priv; } ;
typedef  int fe_sec_tone_mode_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int stv0299_readreg (struct stv0299_state*,int) ; 
 scalar_t__ stv0299_wait_diseqc_idle (struct stv0299_state*,int) ; 
 int stv0299_writeregI (struct stv0299_state*,int,int) ; 

__attribute__((used)) static int stv0299_set_tone (struct dvb_frontend* fe, fe_sec_tone_mode_t tone)
{
	struct stv0299_state* state = fe->demodulator_priv;
	u8 val;

	if (stv0299_wait_diseqc_idle (state, 100) < 0)
		return -ETIMEDOUT;

	val = stv0299_readreg (state, 0x08);

	switch (tone) {
	case SEC_TONE_ON:
		return stv0299_writeregI (state, 0x08, val | 0x3);

	case SEC_TONE_OFF:
		return stv0299_writeregI (state, 0x08, (val & ~0x3) | 0x02);

	default:
		return -EINVAL;
	}
}