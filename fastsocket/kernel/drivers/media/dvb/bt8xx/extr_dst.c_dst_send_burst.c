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
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {scalar_t__ dst_type; int minicmd; int* tx_tuna; } ;
typedef  int fe_sec_mini_cmd_t ;

/* Variables and functions */
 scalar_t__ DST_TYPE_IS_SAT ; 
 int EOPNOTSUPP ; 
#define  SEC_MINI_A 129 
#define  SEC_MINI_B 128 
 int dst_tone_power_cmd (struct dst_state*) ; 

__attribute__((used)) static int dst_send_burst(struct dvb_frontend *fe, fe_sec_mini_cmd_t minicmd)
{
	struct dst_state *state = fe->demodulator_priv;

	if (state->dst_type != DST_TYPE_IS_SAT)
		return -EOPNOTSUPP;
	state->minicmd = minicmd;
	switch (minicmd) {
	case SEC_MINI_A:
		state->tx_tuna[3] = 0x02;
		break;
	case SEC_MINI_B:
		state->tx_tuna[3] = 0xff;
		break;
	}
	return dst_tone_power_cmd(state);
}