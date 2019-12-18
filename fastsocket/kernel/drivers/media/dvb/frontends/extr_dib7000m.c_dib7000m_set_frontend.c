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
struct TYPE_7__ {scalar_t__ transmission_mode; scalar_t__ guard_interval; scalar_t__ constellation; scalar_t__ code_rate_HP; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_8__ {TYPE_3__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_6__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct dib7000m_state* demodulator_priv; } ;
struct dib7000m_state {scalar_t__ agc_state; int /*<<< orphan*/  current_bandwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ FEC_AUTO ; 
 scalar_t__ GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  OUTMODE_HIGH_Z ; 
 int /*<<< orphan*/  OUTMODE_MPEG2_FIFO ; 
 scalar_t__ QAM_AUTO ; 
 scalar_t__ TRANSMISSION_MODE_AUTO ; 
 int dib7000m_agc_startup (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int dib7000m_autosearch_is_irq (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib7000m_autosearch_start (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  dib7000m_get_frontend (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  dib7000m_set_bandwidth (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_set_output_mode (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int dib7000m_tune (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 

__attribute__((used)) static int dib7000m_set_frontend(struct dvb_frontend* fe,
				struct dvb_frontend_parameters *fep)
{
	struct dib7000m_state *state = fe->demodulator_priv;
	int time, ret;

    dib7000m_set_output_mode(state, OUTMODE_HIGH_Z);

	state->current_bandwidth = fep->u.ofdm.bandwidth;
	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(fep->u.ofdm.bandwidth));

	if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe, fep);

	/* start up the AGC */
	state->agc_state = 0;
	do {
		time = dib7000m_agc_startup(fe, fep);
		if (time != -1)
			msleep(time);
	} while (time != -1);

	if (fep->u.ofdm.transmission_mode == TRANSMISSION_MODE_AUTO ||
		fep->u.ofdm.guard_interval    == GUARD_INTERVAL_AUTO ||
		fep->u.ofdm.constellation     == QAM_AUTO ||
		fep->u.ofdm.code_rate_HP      == FEC_AUTO) {
		int i = 800, found;

		dib7000m_autosearch_start(fe, fep);
		do {
			msleep(1);
			found = dib7000m_autosearch_is_irq(fe);
		} while (found == 0 && i--);

		dprintk("autosearch returns: %d",found);
		if (found == 0 || found == 1)
			return 0; // no channel found

		dib7000m_get_frontend(fe, fep);
	}

	ret = dib7000m_tune(fe, fep);

	/* make this a config parameter */
	dib7000m_set_output_mode(state, OUTMODE_MPEG2_FIFO);
	return ret;
}