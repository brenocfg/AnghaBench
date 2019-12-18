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
typedef  int u8 ;
typedef  int u32 ;
struct zl10036_state {int dummy; } ;
struct TYPE_6__ {int symbol_rate; } ;
struct TYPE_7__ {TYPE_2__ qpsk; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; } ;
struct TYPE_5__ {int frequency_min; int frequency_max; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__ info; } ;
struct dvb_frontend {TYPE_4__ ops; struct zl10036_state* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int STATUS_FL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int zl10036_read_status_reg (struct zl10036_state*) ; 
 int zl10036_set_bandwidth (struct zl10036_state*,int) ; 
 int zl10036_set_frequency (struct zl10036_state*,int) ; 
 int zl10036_set_gain_params (struct zl10036_state*,int) ; 

__attribute__((used)) static int zl10036_set_params(struct dvb_frontend *fe,
		struct dvb_frontend_parameters *params)
{
	struct zl10036_state *state = fe->tuner_priv;
	int ret = 0;
	u32 frequency = params->frequency;
	u32 fbw;
	int i;
	u8 c;

	/* ensure correct values
	 * maybe redundant as core already checks this */
	if ((frequency < fe->ops.info.frequency_min)
	||  (frequency > fe->ops.info.frequency_max))
		return -EINVAL;

	/**
	 * alpha = 1.35 for dvb-s
	 * fBW = (alpha*symbolrate)/(2*0.8)
	 * 1.35 / (2*0.8) = 27 / 32
	 */
	fbw = (27 * params->u.qpsk.symbol_rate) / 32;

	/* scale to kHz */
	fbw /= 1000;

	/* Add safe margin of 3MHz */
	fbw += 3000;

	/* setting the charge pump - guessed values */
	if (frequency < 950000)
		return -EINVAL;
	else if (frequency < 1250000)
		c = 0;
	else if (frequency < 1750000)
		c = 1;
	else if (frequency < 2175000)
		c = 2;
	else
		return -EINVAL;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	ret = zl10036_set_gain_params(state, c);
	if (ret < 0)
		goto error;

	ret = zl10036_set_frequency(state, params->frequency);
	if (ret < 0)
		goto error;

	ret = zl10036_set_bandwidth(state, fbw);
	if (ret < 0)
		goto error;

	/* wait for tuner lock - no idea if this is really needed */
	for (i = 0; i < 20; i++) {
		ret = zl10036_read_status_reg(state);
		if (ret < 0)
			goto error;

		/* check Frequency & Phase Lock Bit */
		if (ret & STATUS_FL)
			break;

		msleep(10);
	}

error:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	return ret;
}