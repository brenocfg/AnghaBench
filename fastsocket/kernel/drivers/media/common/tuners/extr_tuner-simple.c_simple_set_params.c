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
struct TYPE_2__ {int /*<<< orphan*/ * adap; } ;
struct tuner_simple_priv {int frequency; scalar_t__ bandwidth; TYPE_1__ i2c_props; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;
struct analog_parameters {int mode; int frequency; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_ANALOG_TV 130 
#define  V4L2_TUNER_DIGITAL_TV 129 
#define  V4L2_TUNER_RADIO 128 
 int simple_set_radio_freq (struct dvb_frontend*,struct analog_parameters*) ; 
 int simple_set_tv_freq (struct dvb_frontend*,struct analog_parameters*) ; 

__attribute__((used)) static int simple_set_params(struct dvb_frontend *fe,
			     struct analog_parameters *params)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;
	int ret = -EINVAL;

	if (priv->i2c_props.adap == NULL)
		return -EINVAL;

	switch (params->mode) {
	case V4L2_TUNER_RADIO:
		ret = simple_set_radio_freq(fe, params);
		priv->frequency = params->frequency * 125 / 2;
		break;
	case V4L2_TUNER_ANALOG_TV:
	case V4L2_TUNER_DIGITAL_TV:
		ret = simple_set_tv_freq(fe, params);
		priv->frequency = params->frequency * 62500;
		break;
	}
	priv->bandwidth = 0;

	return ret;
}