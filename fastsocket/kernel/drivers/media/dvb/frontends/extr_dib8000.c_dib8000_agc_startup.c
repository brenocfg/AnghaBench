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
struct TYPE_3__ {int frequency; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; struct dib8000_state* demodulator_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* agc_control ) (int /*<<< orphan*/ *,int) ;} ;
struct dib8000_state {int tune_state; int /*<<< orphan*/  fe; TYPE_2__ cfg; int /*<<< orphan*/  status; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */
 scalar_t__ BAND_OF_FREQUENCY (int) ; 
#define  CT_AGC_START 131 
#define  CT_AGC_STEP_0 130 
#define  CT_AGC_STEP_1 129 
#define  CT_AGC_STEP_2 128 
 int CT_AGC_STOP ; 
 int /*<<< orphan*/  DIBX000_ADC_ON ; 
 int /*<<< orphan*/  FE_STATUS_TUNE_FAILED ; 
 int dib8000_agc_soft_split (struct dib8000_state*) ; 
 int /*<<< orphan*/  dib8000_restart_agc (struct dib8000_state*) ; 
 int /*<<< orphan*/  dib8000_set_adc_state (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_set_agc_config (struct dib8000_state*,unsigned char) ; 
 int /*<<< orphan*/  dib8000_update_lna (struct dib8000_state*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dib8000_agc_startup(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;
	enum frontend_tune_state *tune_state = &state->tune_state;

	int ret = 0;

	switch (*tune_state) {
	case CT_AGC_START:
		// set power-up level: interf+analog+AGC

		dib8000_set_adc_state(state, DIBX000_ADC_ON);

		if (dib8000_set_agc_config(state, (unsigned char)(BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency / 1000))) != 0) {
			*tune_state = CT_AGC_STOP;
			state->status = FE_STATUS_TUNE_FAILED;
			break;
		}

		ret = 70;
		*tune_state = CT_AGC_STEP_0;
		break;

	case CT_AGC_STEP_0:
		//AGC initialization
		if (state->cfg.agc_control)
			state->cfg.agc_control(&state->fe, 1);

		dib8000_restart_agc(state);

		// wait AGC rough lock time
		ret = 50;
		*tune_state = CT_AGC_STEP_1;
		break;

	case CT_AGC_STEP_1:
		// wait AGC accurate lock time
		ret = 70;

		if (dib8000_update_lna(state))
			// wait only AGC rough lock time
			ret = 50;
		else
			*tune_state = CT_AGC_STEP_2;
		break;

	case CT_AGC_STEP_2:
		dib8000_agc_soft_split(state);

		if (state->cfg.agc_control)
			state->cfg.agc_control(&state->fe, 0);

		*tune_state = CT_AGC_STOP;
		break;
	default:
		ret = dib8000_agc_soft_split(state);
		break;
	}
	return ret;

}