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
struct mb86a16_state {int frequency; int srate; } ;
struct TYPE_3__ {int symbol_rate; } ;
struct TYPE_4__ {TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {int frequency; TYPE_2__ u; } ;
struct dvb_frontend {struct mb86a16_state* demodulator_priv; } ;
typedef  enum dvbfe_search { ____Placeholder_dvbfe_search } dvbfe_search ;

/* Variables and functions */
 int DVBFE_ALGO_SEARCH_FAILED ; 
 int DVBFE_ALGO_SEARCH_SUCCESS ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mb86a16_set_fe (struct mb86a16_state*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static enum dvbfe_search mb86a16_search(struct dvb_frontend *fe,
					struct dvb_frontend_parameters *p)
{
	struct mb86a16_state *state = fe->demodulator_priv;

	state->frequency = p->frequency / 1000;
	state->srate = p->u.qpsk.symbol_rate / 1000;

	if (!mb86a16_set_fe(state)) {
		dprintk(verbose, MB86A16_ERROR, 1, "Succesfully acquired LOCK");
		return DVBFE_ALGO_SEARCH_SUCCESS;
	}

	dprintk(verbose, MB86A16_ERROR, 1, "Lock acquisition failed!");
	return DVBFE_ALGO_SEARCH_FAILED;
}