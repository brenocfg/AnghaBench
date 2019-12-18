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
struct stv090x_state {scalar_t__ frequency; int srate; int search_range; int /*<<< orphan*/  fec; int /*<<< orphan*/  algo; int /*<<< orphan*/  search_mode; int /*<<< orphan*/  delsys; } ;
struct TYPE_3__ {int symbol_rate; } ;
struct TYPE_4__ {TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {scalar_t__ frequency; TYPE_2__ u; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv090x_state* demodulator_priv; } ;
typedef  enum dvbfe_search { ____Placeholder_dvbfe_search } dvbfe_search ;

/* Variables and functions */
 int DVBFE_ALGO_SEARCH_ERROR ; 
 int DVBFE_ALGO_SEARCH_FAILED ; 
 int DVBFE_ALGO_SEARCH_INVALID ; 
 int DVBFE_ALGO_SEARCH_SUCCESS ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STV090x_COLD_SEARCH ; 
 int /*<<< orphan*/  STV090x_PRERR ; 
 scalar_t__ STV090x_RANGEOK ; 
 int /*<<< orphan*/  STV090x_SEARCH_AUTO ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ stv090x_algo (struct stv090x_state*) ; 

__attribute__((used)) static enum dvbfe_search stv090x_search(struct dvb_frontend *fe, struct dvb_frontend_parameters *p)
{
	struct stv090x_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *props = &fe->dtv_property_cache;

	if (p->frequency == 0)
		return DVBFE_ALGO_SEARCH_INVALID;

	state->delsys = props->delivery_system;
	state->frequency = p->frequency;
	state->srate = p->u.qpsk.symbol_rate;
	state->search_mode = STV090x_SEARCH_AUTO;
	state->algo = STV090x_COLD_SEARCH;
	state->fec = STV090x_PRERR;
	if (state->srate > 10000000) {
		dprintk(FE_DEBUG, 1, "Search range: 10 MHz");
		state->search_range = 10000000;
	} else {
		dprintk(FE_DEBUG, 1, "Search range: 5 MHz");
		state->search_range = 5000000;
	}

	if (stv090x_algo(state) == STV090x_RANGEOK) {
		dprintk(FE_DEBUG, 1, "Search success!");
		return DVBFE_ALGO_SEARCH_SUCCESS;
	} else {
		dprintk(FE_DEBUG, 1, "Search failed!");
		return DVBFE_ALGO_SEARCH_FAILED;
	}

	return DVBFE_ALGO_SEARCH_ERROR;
}