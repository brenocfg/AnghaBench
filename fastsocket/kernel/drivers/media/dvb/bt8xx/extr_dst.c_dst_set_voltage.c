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
struct dst_state {int voltage; scalar_t__ dst_type; int diseq_flags; int* tx_tuna; } ;
typedef  int fe_sec_voltage_t ;

/* Variables and functions */
 int ATTEMPT_TUNE ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int HAS_LOCK ; 
 int HAS_POWER ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int dst_tone_power_cmd (struct dst_state*) ; 

__attribute__((used)) static int dst_set_voltage(struct dvb_frontend *fe, fe_sec_voltage_t voltage)
{
	int need_cmd, retval = 0;
	struct dst_state *state = fe->demodulator_priv;

	state->voltage = voltage;
	if (state->dst_type != DST_TYPE_IS_SAT)
		return -EOPNOTSUPP;

	need_cmd = 0;

	switch (voltage) {
	case SEC_VOLTAGE_13:
	case SEC_VOLTAGE_18:
		if ((state->diseq_flags & HAS_POWER) == 0)
			need_cmd = 1;
		state->diseq_flags |= HAS_POWER;
		state->tx_tuna[4] = 0x01;
		break;
	case SEC_VOLTAGE_OFF:
		need_cmd = 1;
		state->diseq_flags &= ~(HAS_POWER | HAS_LOCK | ATTEMPT_TUNE);
		state->tx_tuna[4] = 0x00;
		break;
	default:
		return -EINVAL;
	}

	if (need_cmd)
		retval = dst_tone_power_cmd(state);

	return retval;
}