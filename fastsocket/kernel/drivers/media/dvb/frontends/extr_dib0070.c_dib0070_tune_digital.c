#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend_parameters {int dummy; } ;
struct TYPE_5__ {int frequency; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; struct dib0070_state* tuner_priv; } ;
struct dib0070_wbd_gain_cfg {int freq; int wbd_gain_val; } ;
struct dib0070_tuning {int max_freq; int vco_band; int hfdiv; int vco_multi; int presc; int tuner_enable; int wbdmux; int switch_trim; } ;
struct dib0070_state {int tune_state; int current_rf; int revision; int lo4; int wbd_gain_current; struct dib0070_lna_match const* lna_match; struct dib0070_tuning const* current_tune_table_index; TYPE_2__* cfg; TYPE_4__* fe; } ;
struct dib0070_lna_match {int max_freq; int lna_band; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;
struct TYPE_7__ {scalar_t__ delivery_system; int isdbt_sb_mode; int isdbt_sb_segment_count; int isdbt_sb_segment_idx; } ;
struct TYPE_8__ {TYPE_3__ dtv_property_cache; } ;
struct TYPE_6__ {int freq_offset_khz_vhf; int freq_offset_khz_uhf; int clock_khz; struct dib0070_wbd_gain_cfg* wbd_gain; int /*<<< orphan*/  flip_chip; } ;

/* Variables and functions */
#define  BAND_FM 132 
 int /*<<< orphan*/  BAND_OF_FREQUENCY (int) ; 
 int BAND_SBAND ; 
#define  BAND_VHF 131 
 int CT_TUNER_START ; 
 int CT_TUNER_STEP_0 ; 
 int CT_TUNER_STEP_4 ; 
 int CT_TUNER_STEP_5 ; 
 int CT_TUNER_STOP ; 
#define  DIB0070S_P1A 130 
#define  DIB0070_P1F 129 
#define  DIB0070_P1G 128 
 int FE_CALLBACK_TIME_NEVER ; 
 int LPF ; 
 scalar_t__ SYS_ISDBT ; 
 int dib0070_captrim (struct dib0070_state*,int*) ; 
 struct dib0070_lna_match* dib0070_lna ; 
 struct dib0070_lna_match* dib0070_lna_flip_chip ; 
 int /*<<< orphan*/  dib0070_set_bandwidth (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  dib0070_set_ctrl_lo5 (struct dvb_frontend*,int,int,int,int) ; 
 struct dib0070_tuning* dib0070_tuning_table ; 
 int /*<<< orphan*/  dib0070_write_reg (struct dib0070_state*,int,int) ; 
 struct dib0070_tuning* dib0070s_tuning_table ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 

__attribute__((used)) static int dib0070_tune_digital(struct dvb_frontend *fe, struct dvb_frontend_parameters *ch)
{
    struct dib0070_state *state = fe->tuner_priv;

    const struct dib0070_tuning *tune;
    const struct dib0070_lna_match *lna_match;

    enum frontend_tune_state *tune_state = &state->tune_state;
    int ret = 10; /* 1ms is the default delay most of the time */

    u8  band = (u8)BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency/1000);
    u32 freq = fe->dtv_property_cache.frequency/1000 + (band == BAND_VHF ? state->cfg->freq_offset_khz_vhf : state->cfg->freq_offset_khz_uhf);

#ifdef CONFIG_SYS_ISDBT
    if (state->fe->dtv_property_cache.delivery_system == SYS_ISDBT && state->fe->dtv_property_cache.isdbt_sb_mode == 1)
		if (((state->fe->dtv_property_cache.isdbt_sb_segment_count % 2)
		     && (state->fe->dtv_property_cache.isdbt_sb_segment_idx == ((state->fe->dtv_property_cache.isdbt_sb_segment_count / 2) + 1)))
		    || (((state->fe->dtv_property_cache.isdbt_sb_segment_count % 2) == 0)
			&& (state->fe->dtv_property_cache.isdbt_sb_segment_idx == (state->fe->dtv_property_cache.isdbt_sb_segment_count / 2)))
		    || (((state->fe->dtv_property_cache.isdbt_sb_segment_count % 2) == 0)
			&& (state->fe->dtv_property_cache.isdbt_sb_segment_idx == ((state->fe->dtv_property_cache.isdbt_sb_segment_count / 2) + 1))))
			freq += 850;
#endif
    if (state->current_rf != freq) {

	switch (state->revision) {
	case DIB0070S_P1A:
	    tune = dib0070s_tuning_table;
	    lna_match = dib0070_lna;
	    break;
	default:
	    tune = dib0070_tuning_table;
	    if (state->cfg->flip_chip)
		lna_match = dib0070_lna_flip_chip;
	    else
		lna_match = dib0070_lna;
	    break;
	}
	while (freq > tune->max_freq) /* find the right one */
	    tune++;
	while (freq > lna_match->max_freq) /* find the right one */
	    lna_match++;

	state->current_tune_table_index = tune;
	state->lna_match = lna_match;
    }

    if (*tune_state == CT_TUNER_START) {
	dprintk("Tuning for Band: %hd (%d kHz)", band, freq);
	if (state->current_rf != freq) {
		u8 REFDIV;
		u32 FBDiv, Rest, FREF, VCOF_kHz;
		u8 Den;

		state->current_rf = freq;
		state->lo4 = (state->current_tune_table_index->vco_band << 11) | (state->current_tune_table_index->hfdiv << 7);


		dib0070_write_reg(state, 0x17, 0x30);


		VCOF_kHz = state->current_tune_table_index->vco_multi * freq * 2;

		switch (band) {
		case BAND_VHF:
			REFDIV = (u8) ((state->cfg->clock_khz + 9999) / 10000);
			break;
		case BAND_FM:
			REFDIV = (u8) ((state->cfg->clock_khz) / 1000);
			break;
		default:
			REFDIV = (u8) (state->cfg->clock_khz  / 10000);
			break;
		}
		FREF = state->cfg->clock_khz / REFDIV;



		switch (state->revision) {
		case DIB0070S_P1A:
			FBDiv = (VCOF_kHz / state->current_tune_table_index->presc / FREF);
			Rest  = (VCOF_kHz / state->current_tune_table_index->presc) - FBDiv * FREF;
			break;

		case DIB0070_P1G:
		case DIB0070_P1F:
		default:
			FBDiv = (freq / (FREF / 2));
			Rest  = 2 * freq - FBDiv * FREF;
			break;
		}

		if (Rest < LPF)
			Rest = 0;
		else if (Rest < 2 * LPF)
			Rest = 2 * LPF;
		else if (Rest > (FREF - LPF)) {
			Rest = 0;
			FBDiv += 1;
		} else if (Rest > (FREF - 2 * LPF))
			Rest = FREF - 2 * LPF;
		Rest = (Rest * 6528) / (FREF / 10);

		Den = 1;
		if (Rest > 0) {
			state->lo4 |= (1 << 14) | (1 << 12);
			Den = 255;
		}


		dib0070_write_reg(state, 0x11, (u16)FBDiv);
		dib0070_write_reg(state, 0x12, (Den << 8) | REFDIV);
		dib0070_write_reg(state, 0x13, (u16) Rest);

		if (state->revision == DIB0070S_P1A) {

			if (band == BAND_SBAND) {
				dib0070_set_ctrl_lo5(fe, 2, 4, 3, 0);
				dib0070_write_reg(state, 0x1d, 0xFFFF);
			} else
				dib0070_set_ctrl_lo5(fe, 5, 4, 3, 1);
		}

		dib0070_write_reg(state, 0x20,
			0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001 | state->current_tune_table_index->tuner_enable);

		dprintk("REFDIV: %hd, FREF: %d", REFDIV, FREF);
		dprintk("FBDIV: %d, Rest: %d", FBDiv, Rest);
		dprintk("Num: %hd, Den: %hd, SD: %hd", (u16) Rest, Den, (state->lo4 >> 12) & 0x1);
		dprintk("HFDIV code: %hd", state->current_tune_table_index->hfdiv);
		dprintk("VCO = %hd", state->current_tune_table_index->vco_band);
		dprintk("VCOF: ((%hd*%d) << 1))", state->current_tune_table_index->vco_multi, freq);

		*tune_state = CT_TUNER_STEP_0;
	} else { /* we are already tuned to this frequency - the configuration is correct  */
		ret = 50; /* wakeup time */
		*tune_state = CT_TUNER_STEP_5;
	}
    } else if ((*tune_state > CT_TUNER_START) && (*tune_state < CT_TUNER_STEP_4)) {

	ret = dib0070_captrim(state, tune_state);

    } else if (*tune_state == CT_TUNER_STEP_4) {
	const struct dib0070_wbd_gain_cfg *tmp = state->cfg->wbd_gain;
	if (tmp != NULL) {
		while (freq/1000 > tmp->freq) /* find the right one */
			tmp++;
		dib0070_write_reg(state, 0x0f,
			(0 << 15) | (1 << 14) | (3 << 12)
			| (tmp->wbd_gain_val << 9) | (0 << 8) | (1 << 7)
			| (state->current_tune_table_index->wbdmux << 0));
		state->wbd_gain_current = tmp->wbd_gain_val;
	} else {
			dib0070_write_reg(state, 0x0f,
					  (0 << 15) | (1 << 14) | (3 << 12) | (6 << 9) | (0 << 8) | (1 << 7) | (state->current_tune_table_index->
														wbdmux << 0));
	    state->wbd_gain_current = 6;
	}

	dib0070_write_reg(state, 0x06, 0x3fff);
		dib0070_write_reg(state, 0x07,
				  (state->current_tune_table_index->switch_trim << 11) | (7 << 8) | (state->lna_match->lna_band << 3) | (3 << 0));
	dib0070_write_reg(state, 0x08, (state->lna_match->lna_band << 10) | (3 << 7) | (127));
	dib0070_write_reg(state, 0x0d, 0x0d80);


	dib0070_write_reg(state, 0x18,   0x07ff);
	dib0070_write_reg(state, 0x17, 0x0033);


	*tune_state = CT_TUNER_STEP_5;
    } else if (*tune_state == CT_TUNER_STEP_5) {
	dib0070_set_bandwidth(fe, ch);
	*tune_state = CT_TUNER_STOP;
    } else {
	ret = FE_CALLBACK_TIME_NEVER; /* tuner finished, time to call again infinite */
    }
    return ret;
}