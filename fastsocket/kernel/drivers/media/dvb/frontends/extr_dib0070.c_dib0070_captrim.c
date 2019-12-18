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
typedef  int u32 ;
typedef  int u16 ;
struct dib0070_state {int step; int captrim; int fcaptrim; int adc_diff; int lo4; } ;
typedef  int int8_t ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */
 int CT_TUNER_STEP_0 ; 
 int CT_TUNER_STEP_1 ; 
 int CT_TUNER_STEP_2 ; 
 int CT_TUNER_STEP_3 ; 
 int CT_TUNER_STEP_4 ; 
 int dib0070_read_reg (struct dib0070_state*,int) ; 
 int /*<<< orphan*/  dib0070_write_reg (struct dib0070_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 

__attribute__((used)) static int dib0070_captrim(struct dib0070_state *state, enum frontend_tune_state *tune_state)
{
	int8_t step_sign;
	u16 adc;
	int ret = 0;

	if (*tune_state == CT_TUNER_STEP_0) {

		dib0070_write_reg(state, 0x0f, 0xed10);
		dib0070_write_reg(state, 0x17,    0x0034);

		dib0070_write_reg(state, 0x18, 0x0032);
		state->step = state->captrim = state->fcaptrim = 64;
		state->adc_diff = 3000;
		ret = 20;

	*tune_state = CT_TUNER_STEP_1;
	} else if (*tune_state == CT_TUNER_STEP_1) {
		state->step /= 2;
		dib0070_write_reg(state, 0x14, state->lo4 | state->captrim);
		ret = 15;

		*tune_state = CT_TUNER_STEP_2;
	} else if (*tune_state == CT_TUNER_STEP_2) {

		adc = dib0070_read_reg(state, 0x19);

		dprintk("CAPTRIM=%hd; ADC = %hd (ADC) & %dmV", state->captrim, adc, (u32) adc*(u32)1800/(u32)1024);

		if (adc >= 400) {
			adc -= 400;
			step_sign = -1;
		} else {
			adc = 400 - adc;
			step_sign = 1;
		}

		if (adc < state->adc_diff) {
			dprintk("CAPTRIM=%hd is closer to target (%hd/%hd)", state->captrim, adc, state->adc_diff);
			state->adc_diff = adc;
			state->fcaptrim = state->captrim;



		}
		state->captrim += (step_sign * state->step);

		if (state->step >= 1)
			*tune_state = CT_TUNER_STEP_1;
		else
			*tune_state = CT_TUNER_STEP_3;

	} else if (*tune_state == CT_TUNER_STEP_3) {
		dib0070_write_reg(state, 0x14, state->lo4 | state->fcaptrim);
		dib0070_write_reg(state, 0x18, 0x07ff);
		*tune_state = CT_TUNER_STEP_4;
	}

	return ret;
}