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
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {scalar_t__ current_band; scalar_t__* rf_ramp; TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ use_pwm_agc; } ;

/* Variables and functions */
 scalar_t__ BAND_CBAND ; 
 scalar_t__ BAND_SBAND ; 
 scalar_t__ BAND_VHF ; 
 int /*<<< orphan*/  bb_ramp_pwm_boost ; 
 int /*<<< orphan*/  bb_ramp_pwm_normal ; 
 int /*<<< orphan*/  dib0090_set_bbramp_pwm (struct dib0090_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib0090_set_rframp_pwm (struct dib0090_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  rf_ramp_pwm_cband ; 
 int /*<<< orphan*/  rf_ramp_pwm_sband ; 
 int /*<<< orphan*/  rf_ramp_pwm_uhf ; 
 int /*<<< orphan*/  rf_ramp_pwm_vhf ; 

void dib0090_pwm_gain_reset(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	/* reset the AGC */

	if (state->config->use_pwm_agc) {
#ifdef CONFIG_BAND_SBAND
		if (state->current_band == BAND_SBAND) {
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_sband);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_boost);
		} else
#endif
#ifdef CONFIG_BAND_CBAND
		if (state->current_band == BAND_CBAND) {
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_cband);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
		} else
#endif
#ifdef CONFIG_BAND_VHF
		if (state->current_band == BAND_VHF) {
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_vhf);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
		} else
#endif
		{
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_uhf);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
		}

		if (state->rf_ramp[0] != 0)
			dib0090_write_reg(state, 0x32, (3 << 11));
		else
			dib0090_write_reg(state, 0x32, (0 << 11));

		dib0090_write_reg(state, 0x39, (1 << 10));
	}
}