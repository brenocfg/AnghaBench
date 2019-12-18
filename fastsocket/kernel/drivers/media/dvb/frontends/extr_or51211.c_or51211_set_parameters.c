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
struct or51211_state {scalar_t__ current_frequency; } ;
struct dvb_frontend_parameters {scalar_t__ frequency; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct or51211_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  or51211_setmode (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int or51211_set_parameters(struct dvb_frontend* fe,
				  struct dvb_frontend_parameters *param)
{
	struct or51211_state* state = fe->demodulator_priv;

	/* Change only if we are actually changing the channel */
	if (state->current_frequency != param->frequency) {
		if (fe->ops.tuner_ops.set_params) {
			fe->ops.tuner_ops.set_params(fe, param);
			if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
		}

		/* Set to ATSC mode */
		or51211_setmode(fe,0);

		/* Update current frequency */
		state->current_frequency = param->frequency;
	}
	return 0;
}