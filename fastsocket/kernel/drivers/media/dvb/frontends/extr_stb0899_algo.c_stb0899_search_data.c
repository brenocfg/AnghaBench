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
typedef  int /*<<< orphan*/  u8 ;
struct stb0899_params {long srate; } ;
struct stb0899_internal {long mclk; long sub_range; short derot_freq; scalar_t__ status; int direction; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; TYPE_1__* config; struct stb0899_params params; struct stb0899_internal internal; } ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;
struct TYPE_2__ {short inversion; } ;

/* Variables and functions */
 scalar_t__ CARRIEROK ; 
 int /*<<< orphan*/  CFD_ON ; 
 int /*<<< orphan*/  CFRL ; 
 int /*<<< orphan*/  CFRM ; 
 scalar_t__ DATAOK ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int LSB (short) ; 
 int MAKEWORD16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MSB (short) ; 
 int /*<<< orphan*/  STB0899_CFD ; 
 int /*<<< orphan*/  STB0899_CFRM ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 short abs (short) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,...) ; 
 int /*<<< orphan*/  stb0899_check_carrier (struct stb0899_state*) ; 
 scalar_t__ stb0899_check_data (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_read_regs (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_regs (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum stb0899_status stb0899_search_data(struct stb0899_state *state)
{
	short int derot_freq, derot_step, derot_limit, next_loop = 3;
	u8 cfr[2];
	u8 reg;
	int index = 1;

	struct stb0899_internal *internal = &state->internal;
	struct stb0899_params *params = &state->params;

	derot_step = (params->srate / 4L) / internal->mclk;
	derot_limit = (internal->sub_range / 2L) / internal->mclk;
	derot_freq = internal->derot_freq;

	do {
		if ((internal->status != CARRIEROK) || (stb0899_check_data(state) != DATAOK)) {

			derot_freq += index * internal->direction * derot_step;	/* next zig zag derotator position */
			if (abs(derot_freq) > derot_limit)
				next_loop--;

			if (next_loop) {
				dprintk(state->verbose, FE_DEBUG, 1, "Derot freq=%d, mclk=%d", derot_freq, internal->mclk);
				reg = stb0899_read_reg(state, STB0899_CFD);
				STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
				stb0899_write_reg(state, STB0899_CFD, reg);

				STB0899_SETFIELD_VAL(CFRM, cfr[0], MSB(state->config->inversion * derot_freq));
				STB0899_SETFIELD_VAL(CFRL, cfr[1], LSB(state->config->inversion * derot_freq));
				stb0899_write_regs(state, STB0899_CFRM, cfr, 2); /* derotator frequency	*/

				stb0899_check_carrier(state);
				index++;
			}
		}
		internal->direction = -internal->direction; /* change zig zag direction */
	} while ((internal->status != DATAOK) && next_loop);

	if (internal->status == DATAOK) {
		stb0899_read_regs(state, STB0899_CFRM, cfr, 2); /* get derotator frequency */
		internal->derot_freq = state->config->inversion * MAKEWORD16(cfr[0], cfr[1]);
		dprintk(state->verbose, FE_DEBUG, 1, "------> DATAOK ! Derot Freq=%d", internal->derot_freq);
	}

	return internal->status;
}