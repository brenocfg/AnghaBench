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
struct TYPE_7__ {int /*<<< orphan*/  modulation; int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  fec_inner; } ;
struct TYPE_6__ {int /*<<< orphan*/  bandwidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  fec_inner; } ;
struct TYPE_8__ {TYPE_3__ qam; TYPE_2__ ofdm; TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {TYPE_4__ u; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {scalar_t__ dst_type; int type_flags; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DST_DEBUG ; 
 int DST_TYPE_HAS_OBS_REGS ; 
 scalar_t__ DST_TYPE_IS_CABLE ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 scalar_t__ DST_TYPE_IS_TERR ; 
 unsigned int FE_TUNE_MODE_ONESHOT ; 
 int HZ ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_read_status (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_set_bandwidth (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_set_fec (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_set_freq (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_set_inversion (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_set_modulation (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_set_polarization (struct dst_state*) ; 
 int /*<<< orphan*/  dst_set_symbolrate (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_write_tuna (struct dvb_frontend*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_tune_frontend(struct dvb_frontend* fe,
			    struct dvb_frontend_parameters* p,
			    unsigned int mode_flags,
			    unsigned int *delay,
			    fe_status_t *status)
{
	struct dst_state *state = fe->demodulator_priv;

	if (p != NULL) {
		dst_set_freq(state, p->frequency);
		dprintk(verbose, DST_DEBUG, 1, "Set Frequency=[%d]", p->frequency);

		if (state->dst_type == DST_TYPE_IS_SAT) {
			if (state->type_flags & DST_TYPE_HAS_OBS_REGS)
				dst_set_inversion(state, p->inversion);
			dst_set_fec(state, p->u.qpsk.fec_inner);
			dst_set_symbolrate(state, p->u.qpsk.symbol_rate);
			dst_set_polarization(state);
			dprintk(verbose, DST_DEBUG, 1, "Set Symbolrate=[%d]", p->u.qpsk.symbol_rate);

		} else if (state->dst_type == DST_TYPE_IS_TERR)
			dst_set_bandwidth(state, p->u.ofdm.bandwidth);
		else if (state->dst_type == DST_TYPE_IS_CABLE) {
			dst_set_fec(state, p->u.qam.fec_inner);
			dst_set_symbolrate(state, p->u.qam.symbol_rate);
			dst_set_modulation(state, p->u.qam.modulation);
		}
		dst_write_tuna(fe);
	}

	if (!(mode_flags & FE_TUNE_MODE_ONESHOT))
		dst_read_status(fe, status);

	*delay = HZ/10;
	return 0;
}