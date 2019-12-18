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
struct ves1x93_state {int /*<<< orphan*/  inversion; } ;
struct TYPE_5__ {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  fec_inner; } ;
struct TYPE_6__ {TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  inversion; TYPE_2__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_4__ tuner_ops; } ;
struct dvb_frontend {TYPE_3__ ops; struct ves1x93_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ves1x93_set_fec (struct ves1x93_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ves1x93_set_inversion (struct ves1x93_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ves1x93_set_symbolrate (struct ves1x93_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ves1x93_set_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters *p)
{
	struct ves1x93_state* state = fe->demodulator_priv;

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe, p);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}
	ves1x93_set_inversion (state, p->inversion);
	ves1x93_set_fec (state, p->u.qpsk.fec_inner);
	ves1x93_set_symbolrate (state, p->u.qpsk.symbol_rate);
	state->inversion = p->inversion;

	return 0;
}