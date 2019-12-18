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
struct stb0899_internal {scalar_t__ status; long sub_range; long mclk; int direction; int derot_freq; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; TYPE_1__* config; struct stb0899_params params; struct stb0899_internal internal; } ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;
struct TYPE_2__ {short inversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFRL ; 
 int /*<<< orphan*/  CFRM ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  LSB (short) ; 
 int MAKEWORD16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSB (short) ; 
 scalar_t__ NOTIMING ; 
 int /*<<< orphan*/  STB0899_CFRM ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TIMINGOK ; 
 short abs (short) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ stb0899_check_tmg (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_read_regs (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stb0899_write_regs (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum stb0899_status stb0899_search_tmg(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_params *params = &state->params;

	short int derot_step, derot_freq = 0, derot_limit, next_loop = 3;
	int index = 0;
	u8 cfr[2];

	internal->status = NOTIMING;

	/* timing loop computation & symbol rate optimisation	*/
	derot_limit = (internal->sub_range / 2L) / internal->mclk;
	derot_step = (params->srate / 2L) / internal->mclk;

	while ((stb0899_check_tmg(state) != TIMINGOK) && next_loop) {
		index++;
		derot_freq += index * internal->direction * derot_step;	/* next derot zig zag position	*/

		if (abs(derot_freq) > derot_limit)
			next_loop--;

		if (next_loop) {
			STB0899_SETFIELD_VAL(CFRM, cfr[0], MSB(state->config->inversion * derot_freq));
			STB0899_SETFIELD_VAL(CFRL, cfr[1], LSB(state->config->inversion * derot_freq));
			stb0899_write_regs(state, STB0899_CFRM, cfr, 2); /* derotator frequency		*/
		}
		internal->direction = -internal->direction;	/* Change zigzag direction		*/
	}

	if (internal->status == TIMINGOK) {
		stb0899_read_regs(state, STB0899_CFRM, cfr, 2); /* get derotator frequency		*/
		internal->derot_freq = state->config->inversion * MAKEWORD16(cfr[0], cfr[1]);
		dprintk(state->verbose, FE_DEBUG, 1, "------->TIMING OK ! Derot Freq = %d", internal->derot_freq);
	}

	return internal->status;
}