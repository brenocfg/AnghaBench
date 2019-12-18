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
struct tda18271_priv {int gate; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct TYPE_4__ {int (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__ analog_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct tda18271_priv* tuner_priv; } ;
typedef  enum tda18271_i2c_gate { ____Placeholder_tda18271_i2c_gate } tda18271_i2c_gate ;

/* Variables and functions */
 int EINVAL ; 
#define  TDA18271_ANALOG 132 
#define  TDA18271_DIGITAL 131 
#define  TDA18271_GATE_ANALOG 130 
#define  TDA18271_GATE_AUTO 129 
#define  TDA18271_GATE_DIGITAL 128 
 int stub1 (struct dvb_frontend*,int) ; 
 int stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int tda18271_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	enum tda18271_i2c_gate gate;
	int ret = 0;

	switch (priv->gate) {
	case TDA18271_GATE_DIGITAL:
	case TDA18271_GATE_ANALOG:
		gate = priv->gate;
		break;
	case TDA18271_GATE_AUTO:
	default:
		switch (priv->mode) {
		case TDA18271_DIGITAL:
			gate = TDA18271_GATE_DIGITAL;
			break;
		case TDA18271_ANALOG:
		default:
			gate = TDA18271_GATE_ANALOG;
			break;
		}
	}

	switch (gate) {
	case TDA18271_GATE_ANALOG:
		if (fe->ops.analog_ops.i2c_gate_ctrl)
			ret = fe->ops.analog_ops.i2c_gate_ctrl(fe, enable);
		break;
	case TDA18271_GATE_DIGITAL:
		if (fe->ops.i2c_gate_ctrl)
			ret = fe->ops.i2c_gate_ctrl(fe, enable);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}