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
struct tuner_state {int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  frequency; } ;
struct stb6100_state {int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct stb6100_state* tuner_priv; } ;
typedef  enum tuner_param { ____Placeholder_tuner_param } tuner_param ;

/* Variables and functions */
#define  DVBFE_TUNER_BANDWIDTH 132 
#define  DVBFE_TUNER_FREQUENCY 131 
#define  DVBFE_TUNER_IFFREQ 130 
#define  DVBFE_TUNER_REFCLOCK 129 
#define  DVBFE_TUNER_TUNERSTEP 128 
 int /*<<< orphan*/  stb6100_set_bandwidth (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb6100_set_frequency (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb6100_set_state(struct dvb_frontend *fe,
			     enum tuner_param param,
			     struct tuner_state *state)
{
	struct stb6100_state *tstate = fe->tuner_priv;

	switch (param) {
	case DVBFE_TUNER_FREQUENCY:
		stb6100_set_frequency(fe, state->frequency);
		tstate->frequency = state->frequency;
		break;
	case DVBFE_TUNER_TUNERSTEP:
		break;
	case DVBFE_TUNER_IFFREQ:
		break;
	case DVBFE_TUNER_BANDWIDTH:
		stb6100_set_bandwidth(fe, state->bandwidth);
		tstate->bandwidth = state->bandwidth;
		break;
	case DVBFE_TUNER_REFCLOCK:
		break;
	default:
		break;
	}

	return 0;
}