#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mxl5007t_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct mxl5007t_state* tuner_priv; } ;

/* Variables and functions */
 int mxl5007t_write_reg (struct mxl5007t_state*,int,int) ; 
 int /*<<< orphan*/  mxl_fail (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mxl5007t_sleep(struct dvb_frontend *fe)
{
	struct mxl5007t_state *state = fe->tuner_priv;
	int ret;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* enter standby mode */
	ret = mxl5007t_write_reg(state, 0x01, 0x00);
	mxl_fail(ret);
	ret = mxl5007t_write_reg(state, 0x0f, 0x00);
	mxl_fail(ret);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return ret;
}