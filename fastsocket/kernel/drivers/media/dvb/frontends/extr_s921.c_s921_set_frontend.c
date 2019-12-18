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
struct s921_state {int /*<<< orphan*/  currentfreq; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct s921_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int s921_pll_tune (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 

__attribute__((used)) static int s921_set_frontend(struct dvb_frontend *fe,
	struct dvb_frontend_parameters *p)
{
	struct s921_state *state = fe->demodulator_priv;
	int rc;

	dprintk("\n");

	/* FIXME: We don't know how to use non-auto mode */

	rc = s921_pll_tune(fe, p);
	if (rc < 0)
		return rc;

	state->currentfreq = p->frequency;

	return 0;
}