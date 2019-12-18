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
struct mxl5005s_state {int Mode; int RF_LO; int RF_IN; int TG_LO; scalar_t__ IF_Mode; int Chan_Bandwidth; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static void MXL_SynthRFTGLO_Calc(struct dvb_frontend *fe)
{
	struct mxl5005s_state *state = fe->tuner_priv;

	if (state->Mode == 1) /* Digital Mode */ {
			/* remove 20.48MHz setting for 2.6.10 */
			state->RF_LO = state->RF_IN;
			/* change for 2.6.6 */
			state->TG_LO = state->RF_IN - 750000;
	} else /* Analog Mode */ {
		if (state->IF_Mode == 0) /* Analog Zero IF mode */ {
			state->RF_LO = state->RF_IN - 400000;
			state->TG_LO = state->RF_IN - 1750000;
		} else /* Analog Low IF mode */ {
			state->RF_LO = state->RF_IN - state->Chan_Bandwidth/2;
			state->TG_LO = state->RF_IN -
				state->Chan_Bandwidth + 500000;
		}
	}
}