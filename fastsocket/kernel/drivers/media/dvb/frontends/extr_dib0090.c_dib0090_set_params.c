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
typedef  int uint32_t ;
struct dvb_frontend_parameters {int dummy; } ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {scalar_t__ tune_state; } ;

/* Variables and functions */
 scalar_t__ CT_TUNER_START ; 
 scalar_t__ CT_TUNER_STOP ; 
 int FE_CALLBACK_TIME_NEVER ; 
 int dib0090_tune (struct dvb_frontend*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib0090_set_params(struct dvb_frontend *fe, struct dvb_frontend_parameters *p)
{
	struct dib0090_state *state = fe->tuner_priv;
	uint32_t ret;

	state->tune_state = CT_TUNER_START;

	do {
		ret = dib0090_tune(fe);
		if (ret != FE_CALLBACK_TIME_NEVER)
			msleep(ret / 10);
		else
			break;
	} while (state->tune_state != CT_TUNER_STOP);

	return 0;
}