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
struct microtune_priv {int frequency; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;
struct analog_parameters {int mode; int frequency; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_ANALOG_TV 130 
#define  V4L2_TUNER_DIGITAL_TV 129 
#define  V4L2_TUNER_RADIO 128 
 int mt2050_set_radio_freq (struct dvb_frontend*,struct analog_parameters*) ; 
 int mt2050_set_tv_freq (struct dvb_frontend*,struct analog_parameters*) ; 

__attribute__((used)) static int mt2050_set_params(struct dvb_frontend *fe,
			     struct analog_parameters *params)
{
	struct microtune_priv *priv = fe->tuner_priv;
	int ret = -EINVAL;

	switch (params->mode) {
	case V4L2_TUNER_RADIO:
		ret = mt2050_set_radio_freq(fe, params);
		priv->frequency = params->frequency * 125 / 2;
		break;
	case V4L2_TUNER_ANALOG_TV:
	case V4L2_TUNER_DIGITAL_TV:
		ret = mt2050_set_tv_freq(fe, params);
		priv->frequency = params->frequency * 62500;
		break;
	}

	return ret;
}