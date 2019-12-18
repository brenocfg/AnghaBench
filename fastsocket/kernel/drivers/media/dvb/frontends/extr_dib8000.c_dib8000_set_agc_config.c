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
typedef  int u8 ;
struct dibx000_agc_config {int band_caps; int setup; int inv_gain; int time_stabiliz; int alpha_level; int thlock; int alpha_mant; int alpha_exp; int beta_mant; int beta_exp; int wbd_ref; int wbd_sel; int perform_agc_softsplit; int wbd_alpha; int agc1_max; int agc1_min; int agc2_max; int agc2_min; int agc1_pt1; int agc1_pt2; int agc1_slope1; int agc1_slope2; int agc2_pt1; int agc2_pt2; int agc2_slope1; int agc2_slope2; int agc1_pt3; int wbd_inv; } ;
struct TYPE_2__ {int agc_config_count; struct dibx000_agc_config* agc; } ;
struct dib8000_state {int current_band; scalar_t__ wbd_ref; struct dibx000_agc_config* current_agc; TYPE_1__ cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 

__attribute__((used)) static int dib8000_set_agc_config(struct dib8000_state *state, u8 band)
{
	struct dibx000_agc_config *agc = NULL;
	int i;
	if (state->current_band == band && state->current_agc != NULL)
		return 0;
	state->current_band = band;

	for (i = 0; i < state->cfg.agc_config_count; i++)
		if (state->cfg.agc[i].band_caps & band) {
			agc = &state->cfg.agc[i];
			break;
		}

	if (agc == NULL) {
		dprintk("no valid AGC configuration found for band 0x%02x", band);
		return -EINVAL;
	}

	state->current_agc = agc;

	/* AGC */
	dib8000_write_word(state, 76, agc->setup);
	dib8000_write_word(state, 77, agc->inv_gain);
	dib8000_write_word(state, 78, agc->time_stabiliz);
	dib8000_write_word(state, 101, (agc->alpha_level << 12) | agc->thlock);

	// Demod AGC loop configuration
	dib8000_write_word(state, 102, (agc->alpha_mant << 5) | agc->alpha_exp);
	dib8000_write_word(state, 103, (agc->beta_mant << 6) | agc->beta_exp);

	dprintk("WBD: ref: %d, sel: %d, active: %d, alpha: %d",
		state->wbd_ref != 0 ? state->wbd_ref : agc->wbd_ref, agc->wbd_sel, !agc->perform_agc_softsplit, agc->wbd_sel);

	/* AGC continued */
	if (state->wbd_ref != 0)
		dib8000_write_word(state, 106, state->wbd_ref);
	else			// use default
		dib8000_write_word(state, 106, agc->wbd_ref);
	dib8000_write_word(state, 107, (agc->wbd_alpha << 9) | (agc->perform_agc_softsplit << 8));
	dib8000_write_word(state, 108, agc->agc1_max);
	dib8000_write_word(state, 109, agc->agc1_min);
	dib8000_write_word(state, 110, agc->agc2_max);
	dib8000_write_word(state, 111, agc->agc2_min);
	dib8000_write_word(state, 112, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib8000_write_word(state, 113, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib8000_write_word(state, 114, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib8000_write_word(state, 115, (agc->agc2_slope1 << 8) | agc->agc2_slope2);

	dib8000_write_word(state, 75, agc->agc1_pt3);
	dib8000_write_word(state, 923, (dib8000_read_word(state, 923) & 0xffe3) | (agc->wbd_inv << 4) | (agc->wbd_sel << 2));	/*LB : 929 -> 923 */

	return 0;
}