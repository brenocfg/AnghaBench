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
typedef  int u32 ;
struct stb0899_internal {int srate; int srch_range; int derot_percent; int lock; int /*<<< orphan*/  tuner_bw; int /*<<< orphan*/  freq; } ;
struct stb0899_params {int srate; int /*<<< orphan*/  freq; } ;
struct stb0899_state {int delsys; int /*<<< orphan*/  verbose; int /*<<< orphan*/  frontend; struct stb0899_config* config; struct stb0899_internal internal; struct stb0899_params params; } ;
struct stb0899_config {int /*<<< orphan*/  (* tuner_get_bandwidth ) (struct dvb_frontend*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* tuner_set_bandwidth ) (struct dvb_frontend*,int) ;int /*<<< orphan*/  hi_clk; int /*<<< orphan*/  lo_clk; int /*<<< orphan*/  (* tuner_set_rfsiggain ) (struct dvb_frontend*,int) ;} ;
struct TYPE_3__ {int symbol_rate; } ;
struct TYPE_4__ {TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {TYPE_2__ u; int /*<<< orphan*/  frequency; } ;
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stb0899_state* demodulator_priv; } ;
typedef  enum dvbfe_search { ____Placeholder_dvbfe_search } dvbfe_search ;

/* Variables and functions */
 int DVBFE_ALGO_SEARCH_ERROR ; 
 int DVBFE_ALGO_SEARCH_FAILED ; 
 int DVBFE_ALGO_SEARCH_INVALID ; 
 int DVBFE_ALGO_SEARCH_SUCCESS ; 
 int /*<<< orphan*/  DVBS2_FEC_LOCK ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 scalar_t__ INRANGE (int,int,int) ; 
 int /*<<< orphan*/  RANGEOK ; 
 int /*<<< orphan*/  STB0899_AGCRFCFG ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stb0899_carr_width (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_dvbs2_algo (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_dvbs_algo (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_i2c_gate_ctrl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stb0899_set_delivery (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_set_iterations (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_set_mclk (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub5 (struct dvb_frontend*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum dvbfe_search stb0899_search(struct dvb_frontend *fe, struct dvb_frontend_parameters *p)
{
	struct stb0899_state *state = fe->demodulator_priv;
	struct stb0899_params *i_params = &state->params;
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_config *config = state->config;
	struct dtv_frontend_properties *props = &fe->dtv_property_cache;

	u32 SearchRange, gain;

	i_params->freq	= p->frequency;
	i_params->srate = p->u.qpsk.symbol_rate;
	state->delsys = props->delivery_system;
	dprintk(state->verbose, FE_DEBUG, 1, "delivery system=%d", state->delsys);

	SearchRange = 10000000;
	dprintk(state->verbose, FE_DEBUG, 1, "Frequency=%d, Srate=%d", i_params->freq, i_params->srate);
	/* checking Search Range is meaningless for a fixed 3 Mhz			*/
	if (INRANGE(i_params->srate, 1000000, 45000000)) {
		dprintk(state->verbose, FE_DEBUG, 1, "Parameters IN RANGE");
		stb0899_set_delivery(state);

		if (state->config->tuner_set_rfsiggain) {
			if (internal->srate > 15000000)
				gain =  8; /* 15Mb < srate < 45Mb, gain = 8dB	*/
			else if (internal->srate > 5000000)
				gain = 12; /*  5Mb < srate < 15Mb, gain = 12dB	*/
			else
				gain = 14; /*  1Mb < srate <  5Mb, gain = 14db	*/
			state->config->tuner_set_rfsiggain(fe, gain);
		}

		if (i_params->srate <= 5000000)
			stb0899_set_mclk(state, config->lo_clk);
		else
			stb0899_set_mclk(state, config->hi_clk);

		switch (state->delsys) {
		case SYS_DVBS:
		case SYS_DSS:
			dprintk(state->verbose, FE_DEBUG, 1, "DVB-S delivery system");
			internal->freq	= i_params->freq;
			internal->srate	= i_params->srate;
			/*
			 * search = user search range +
			 *	    500Khz +
			 *	    2 * Tuner_step_size +
			 *	    10% of the symbol rate
			 */
			internal->srch_range	= SearchRange + 1500000 + (i_params->srate / 5);
			internal->derot_percent	= 30;

			/* What to do for tuners having no bandwidth setup ?	*/
			/* enable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 1);

			if (state->config->tuner_set_bandwidth)
				state->config->tuner_set_bandwidth(fe, (13 * (stb0899_carr_width(state) + SearchRange)) / 10);
			if (state->config->tuner_get_bandwidth)
				state->config->tuner_get_bandwidth(fe, &internal->tuner_bw);

			/* disable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 0);

			/* Set DVB-S1 AGC		*/
			stb0899_write_reg(state, STB0899_AGCRFCFG, 0x11);

			/* Run the search algorithm	*/
			dprintk(state->verbose, FE_DEBUG, 1, "running DVB-S search algo ..");
			if (stb0899_dvbs_algo(state)	== RANGEOK) {
				internal->lock		= 1;
				dprintk(state->verbose, FE_DEBUG, 1,
					"-------------------------------------> DVB-S LOCK !");

//				stb0899_write_reg(state, STB0899_ERRCTRL1, 0x3d); /* Viterbi Errors	*/
//				internal->v_status = stb0899_read_reg(state, STB0899_VSTATUS);
//				internal->err_ctrl = stb0899_read_reg(state, STB0899_ERRCTRL1);
//				dprintk(state->verbose, FE_DEBUG, 1, "VSTATUS=0x%02x", internal->v_status);
//				dprintk(state->verbose, FE_DEBUG, 1, "ERR_CTRL=0x%02x", internal->err_ctrl);

				return DVBFE_ALGO_SEARCH_SUCCESS;
			} else {
				internal->lock		= 0;

				return DVBFE_ALGO_SEARCH_FAILED;
			}
			break;
		case SYS_DVBS2:
			internal->freq			= i_params->freq;
			internal->srate			= i_params->srate;
			internal->srch_range		= SearchRange;

			/* enable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 1);

			if (state->config->tuner_set_bandwidth)
				state->config->tuner_set_bandwidth(fe, (stb0899_carr_width(state) + SearchRange));
			if (state->config->tuner_get_bandwidth)
				state->config->tuner_get_bandwidth(fe, &internal->tuner_bw);

			/* disable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 0);

//			pParams->SpectralInv		= pSearch->IQ_Inversion;

			/* Set DVB-S2 AGC		*/
			stb0899_write_reg(state, STB0899_AGCRFCFG, 0x1c);

			/* Set IterScale =f(MCLK,SYMB)	*/
			stb0899_set_iterations(state);

			/* Run the search algorithm	*/
			dprintk(state->verbose, FE_DEBUG, 1, "running DVB-S2 search algo ..");
			if (stb0899_dvbs2_algo(state)	== DVBS2_FEC_LOCK) {
				internal->lock		= 1;
				dprintk(state->verbose, FE_DEBUG, 1,
					"-------------------------------------> DVB-S2 LOCK !");

//				stb0899_write_reg(state, STB0899_ERRCTRL1, 0xb6); /* Packet Errors	*/
//				internal->v_status = stb0899_read_reg(state, STB0899_VSTATUS);
//				internal->err_ctrl = stb0899_read_reg(state, STB0899_ERRCTRL1);

				return DVBFE_ALGO_SEARCH_SUCCESS;
			} else {
				internal->lock		= 0;

				return DVBFE_ALGO_SEARCH_FAILED;
			}
			break;
		default:
			dprintk(state->verbose, FE_ERROR, 1, "Unsupported delivery system");
			return DVBFE_ALGO_SEARCH_INVALID;
		}
	}

	return DVBFE_ALGO_SEARCH_ERROR;
}