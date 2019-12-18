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
struct xc5000_priv {TYPE_1__ i2c_props; } ;
struct dvb_frontend {struct xc5000_priv* tuner_priv; } ;
struct analog_parameters {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_ANALOG_TV 130 
#define  V4L2_TUNER_DIGITAL_TV 129 
#define  V4L2_TUNER_RADIO 128 
 scalar_t__ XC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 scalar_t__ xc5000_is_firmware_loaded (struct dvb_frontend*) ; 
 int xc5000_set_radio_freq (struct dvb_frontend*,struct analog_parameters*) ; 
 int xc5000_set_tv_freq (struct dvb_frontend*,struct analog_parameters*) ; 
 scalar_t__ xc_load_fw_and_init_tuner (struct dvb_frontend*) ; 

__attribute__((used)) static int xc5000_set_analog_params(struct dvb_frontend *fe,
			     struct analog_parameters *params)
{
	struct xc5000_priv *priv = fe->tuner_priv;
	int ret = -EINVAL;

	if (priv->i2c_props.adap == NULL)
		return -EINVAL;

	if (xc5000_is_firmware_loaded(fe) != XC_RESULT_SUCCESS) {
		if (xc_load_fw_and_init_tuner(fe) != XC_RESULT_SUCCESS) {
			dprintk(1, "Unable to load firmware and init tuner\n");
			return -EINVAL;
		}
	}

	switch (params->mode) {
	case V4L2_TUNER_RADIO:
		ret = xc5000_set_radio_freq(fe, params);
		break;
	case V4L2_TUNER_ANALOG_TV:
	case V4L2_TUNER_DIGITAL_TV:
		ret = xc5000_set_tv_freq(fe, params);
		break;
	}

	return ret;
}