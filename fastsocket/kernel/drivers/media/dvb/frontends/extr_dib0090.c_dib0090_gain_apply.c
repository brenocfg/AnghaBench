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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct dib0090_state {int* rf_ramp; int rf_gain_limit; int* bb_ramp; int current_gain; int* gain; int rf_lt_def; int bb_1_def; int* gain_reg; } ;
typedef  int s16 ;

/* Variables and functions */
 int GAIN_ALPHA ; 
 int WBD_ALPHA ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/ * gain_reg_addr ; 

__attribute__((used)) static void dib0090_gain_apply(struct dib0090_state *state, s16 gain_delta, s16 top_delta, u8 force)
{
	u16 rf, bb, ref;
	u16 i, v, gain_reg[4] = { 0 }, gain;
	const u16 *g;

	if (top_delta < -511)
		top_delta = -511;
	if (top_delta > 511)
		top_delta = 511;

	if (force) {
		top_delta *= (1 << WBD_ALPHA);
		gain_delta *= (1 << GAIN_ALPHA);
	}

	if (top_delta >= ((s16) (state->rf_ramp[0] << WBD_ALPHA) - state->rf_gain_limit))	/* overflow */
		state->rf_gain_limit = state->rf_ramp[0] << WBD_ALPHA;
	else
		state->rf_gain_limit += top_delta;

	if (state->rf_gain_limit < 0)	/*underflow */
		state->rf_gain_limit = 0;

	/* use gain as a temporary variable and correct current_gain */
	gain = ((state->rf_gain_limit >> WBD_ALPHA) + state->bb_ramp[0]) << GAIN_ALPHA;
	if (gain_delta >= ((s16) gain - state->current_gain))	/* overflow */
		state->current_gain = gain;
	else
		state->current_gain += gain_delta;
	/* cannot be less than 0 (only if gain_delta is less than 0 we can have current_gain < 0) */
	if (state->current_gain < 0)
		state->current_gain = 0;

	/* now split total gain to rf and bb gain */
	gain = state->current_gain >> GAIN_ALPHA;

	/* requested gain is bigger than rf gain limit - ACI/WBD adjustment */
	if (gain > (state->rf_gain_limit >> WBD_ALPHA)) {
		rf = state->rf_gain_limit >> WBD_ALPHA;
		bb = gain - rf;
		if (bb > state->bb_ramp[0])
			bb = state->bb_ramp[0];
	} else {		/* high signal level -> all gains put on RF */
		rf = gain;
		bb = 0;
	}

	state->gain[0] = rf;
	state->gain[1] = bb;

	/* software ramp */
	/* Start with RF gains */
	g = state->rf_ramp + 1;	/* point on RF LNA1 max gain */
	ref = rf;
	for (i = 0; i < 7; i++) {	/* Go over all amplifiers => 5RF amps + 2 BB amps = 7 amps */
		if (g[0] == 0 || ref < (g[1] - g[0]))	/* if total gain of the current amp is null or this amp is not concerned because it starts to work from an higher gain value */
			v = 0;	/* force the gain to write for the current amp to be null */
		else if (ref >= g[1])	/* Gain to set is higher than the high working point of this amp */
			v = g[2];	/* force this amp to be full gain */
		else		/* compute the value to set to this amp because we are somewhere in his range */
			v = ((ref - (g[1] - g[0])) * g[2]) / g[0];

		if (i == 0)	/* LNA 1 reg mapping */
			gain_reg[0] = v;
		else if (i == 1)	/* LNA 2 reg mapping */
			gain_reg[0] |= v << 7;
		else if (i == 2)	/* LNA 3 reg mapping */
			gain_reg[1] = v;
		else if (i == 3)	/* LNA 4 reg mapping */
			gain_reg[1] |= v << 7;
		else if (i == 4)	/* CBAND LNA reg mapping */
			gain_reg[2] = v | state->rf_lt_def;
		else if (i == 5)	/* BB gain 1 reg mapping */
			gain_reg[3] = v << 3;
		else if (i == 6)	/* BB gain 2 reg mapping */
			gain_reg[3] |= v << 8;

		g += 3;		/* go to next gain bloc */

		/* When RF is finished, start with BB */
		if (i == 4) {
			g = state->bb_ramp + 1;	/* point on BB gain 1 max gain */
			ref = bb;
		}
	}
	gain_reg[3] |= state->bb_1_def;
	gain_reg[3] |= ((bb % 10) * 100) / 125;

#ifdef DEBUG_AGC
	dprintk("GA CALC: DB: %3d(rf) + %3d(bb) = %3d gain_reg[0]=%04x gain_reg[1]=%04x gain_reg[2]=%04x gain_reg[0]=%04x", rf, bb, rf + bb,
		gain_reg[0], gain_reg[1], gain_reg[2], gain_reg[3]);
#endif

	/* Write the amplifier regs */
	for (i = 0; i < 4; i++) {
		v = gain_reg[i];
		if (force || state->gain_reg[i] != v) {
			state->gain_reg[i] = v;
			dib0090_write_reg(state, gain_reg_addr[i], v);
		}
	}
}