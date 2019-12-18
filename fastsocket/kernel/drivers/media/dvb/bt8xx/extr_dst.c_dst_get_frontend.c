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
struct TYPE_7__ {int /*<<< orphan*/  modulation; void* fec_inner; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  bandwidth; } ;
struct TYPE_5__ {void* fec_inner; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_8__ {TYPE_3__ qam; TYPE_2__ ofdm; TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {TYPE_4__ u; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {scalar_t__ dst_type; int type_flags; int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  inversion; int /*<<< orphan*/  decode_freq; } ;

/* Variables and functions */
 int DST_TYPE_HAS_OBS_REGS ; 
 scalar_t__ DST_TYPE_IS_CABLE ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 scalar_t__ DST_TYPE_IS_TERR ; 
 void* dst_get_fec (struct dst_state*) ; 
 int /*<<< orphan*/  dst_get_modulation (struct dst_state*) ; 

__attribute__((used)) static int dst_get_frontend(struct dvb_frontend *fe, struct dvb_frontend_parameters *p)
{
	struct dst_state *state = fe->demodulator_priv;

	p->frequency = state->decode_freq;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		if (state->type_flags & DST_TYPE_HAS_OBS_REGS)
			p->inversion = state->inversion;
		p->u.qpsk.symbol_rate = state->symbol_rate;
		p->u.qpsk.fec_inner = dst_get_fec(state);
	} else if (state->dst_type == DST_TYPE_IS_TERR) {
		p->u.ofdm.bandwidth = state->bandwidth;
	} else if (state->dst_type == DST_TYPE_IS_CABLE) {
		p->u.qam.symbol_rate = state->symbol_rate;
		p->u.qam.fec_inner = dst_get_fec(state);
		p->u.qam.modulation = dst_get_modulation(state);
	}

	return 0;
}