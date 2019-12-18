#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ofdm; } ;
struct dvb_frontend_parameters {TYPE_2__ u; int /*<<< orphan*/  inversion; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_3__ tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct cx22700_state* demodulator_priv; } ;
struct cx22700_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx22700_set_inversion (struct cx22700_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx22700_set_tps (struct cx22700_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx22700_writereg (struct cx22700_state*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx22700_set_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters *p)
{
	struct cx22700_state* state = fe->demodulator_priv;

	cx22700_writereg (state, 0x00, 0x02); /* XXX CHECKME: soft reset*/
	cx22700_writereg (state, 0x00, 0x00);

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe, p);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	cx22700_set_inversion (state, p->inversion);
	cx22700_set_tps (state, &p->u.ofdm);
	cx22700_writereg (state, 0x37, 0x01);  /* PAL loop filter off */
	cx22700_writereg (state, 0x00, 0x01);  /* restart acquire */

	return 0;
}