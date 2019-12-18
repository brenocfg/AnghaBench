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
struct stv0900_state {int demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {int* symbol_rate; int* srch_range; int chip_id; int* freq; int* bw; int* tuner_type; int mclk; int /*<<< orphan*/  rolloff; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  CFRINIT0 ; 
 int /*<<< orphan*/  CFRINIT1 ; 
 int /*<<< orphan*/  CFR_INIT0 ; 
 int /*<<< orphan*/  CFR_INIT1 ; 
 int /*<<< orphan*/  DMDISTATE ; 
 int FALSE ; 
 int /*<<< orphan*/  LSB (int) ; 
 int /*<<< orphan*/  MSB (int) ; 
 scalar_t__ TRUE ; 
 int stv0900_carrier_width (int,int /*<<< orphan*/ ) ; 
 scalar_t__ stv0900_check_timing_lock (struct stv0900_internal*,int) ; 
 int stv0900_get_demod_lock (struct stv0900_internal*,int,int) ; 
 int /*<<< orphan*/  stv0900_set_tuner (struct dvb_frontend*,int,int) ; 
 int /*<<< orphan*/  stv0900_set_tuner_auto (struct stv0900_internal*,int,int,int) ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0900_get_demod_cold_lock(struct dvb_frontend *fe,
					s32 demod_timeout)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;
	int	lock = FALSE,
		d = demod;
	s32	srate,
		search_range,
		locktimeout,
		currier_step,
		nb_steps,
		current_step,
		direction,
		tuner_freq,
		timeout,
		freq;

	srate = intp->symbol_rate[d];
	search_range = intp->srch_range[d];

	if (srate >= 10000000)
		locktimeout = demod_timeout / 3;
	else
		locktimeout = demod_timeout / 2;

	lock = stv0900_get_demod_lock(intp, d, locktimeout);

	if (lock != FALSE)
		return lock;

	if (srate >= 10000000) {
		if (stv0900_check_timing_lock(intp, d) == TRUE) {
			stv0900_write_reg(intp, DMDISTATE, 0x1f);
			stv0900_write_reg(intp, DMDISTATE, 0x15);
			lock = stv0900_get_demod_lock(intp, d, demod_timeout);
		} else
			lock = FALSE;

		return lock;
	}

	if (intp->chip_id <= 0x20) {
		if (srate <= 1000000)
			currier_step = 500;
		else if (srate <= 4000000)
			currier_step = 1000;
		else if (srate <= 7000000)
			currier_step = 2000;
		else if (srate <= 10000000)
			currier_step = 3000;
		else
			currier_step = 5000;

		if (srate >= 2000000) {
			timeout = (demod_timeout / 3);
			if (timeout > 1000)
				timeout = 1000;
		} else
			timeout = (demod_timeout / 2);
	} else {
		/*cut 3.0 */
		currier_step = srate / 4000;
		timeout = (demod_timeout * 3) / 4;
	}

	nb_steps = ((search_range / 1000) / currier_step);

	if ((nb_steps % 2) != 0)
		nb_steps += 1;

	if (nb_steps <= 0)
		nb_steps = 2;
	else if (nb_steps > 12)
		nb_steps = 12;

	current_step = 1;
	direction = 1;

	if (intp->chip_id <= 0x20) {
		tuner_freq = intp->freq[d];
		intp->bw[d] = stv0900_carrier_width(intp->symbol_rate[d],
				intp->rolloff) + intp->symbol_rate[d];
	} else
		tuner_freq = 0;

	while ((current_step <= nb_steps) && (lock == FALSE)) {
		if (direction > 0)
			tuner_freq += (current_step * currier_step);
		else
			tuner_freq -= (current_step * currier_step);

		if (intp->chip_id <= 0x20) {
			if (intp->tuner_type[d] == 3)
				stv0900_set_tuner_auto(intp, tuner_freq,
						intp->bw[d], demod);
			else
				stv0900_set_tuner(fe, tuner_freq, intp->bw[d]);

			stv0900_write_reg(intp, DMDISTATE, 0x1c);
			stv0900_write_reg(intp, CFRINIT1, 0);
			stv0900_write_reg(intp, CFRINIT0, 0);
			stv0900_write_reg(intp, DMDISTATE, 0x1f);
			stv0900_write_reg(intp, DMDISTATE, 0x15);
		} else {
			stv0900_write_reg(intp, DMDISTATE, 0x1c);
			freq = (tuner_freq * 65536) / (intp->mclk / 1000);
			stv0900_write_bits(intp, CFR_INIT1, MSB(freq));
			stv0900_write_bits(intp, CFR_INIT0, LSB(freq));
			stv0900_write_reg(intp, DMDISTATE, 0x1f);
			stv0900_write_reg(intp, DMDISTATE, 0x05);
		}

		lock = stv0900_get_demod_lock(intp, d, timeout);
		direction *= -1;
		current_step++;
	}

	return	lock;
}