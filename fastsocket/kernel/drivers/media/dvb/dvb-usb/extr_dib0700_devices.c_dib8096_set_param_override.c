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
typedef  int u8 ;
typedef  int u16 ;
struct dvb_usb_adapter {struct dib0700_adapter_state* priv; } ;
struct dvb_frontend_parameters {int frequency; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dib0700_adapter_state {int (* set_param_save ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;
struct TYPE_2__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int BAND_CBAND ; 
 int BAND_OF_FREQUENCY (int) ; 
#define  BAND_UHF 129 
#define  BAND_VHF 128 
 int /*<<< orphan*/  CT_AGC_START ; 
 int CT_AGC_STEP_0 ; 
 int CT_AGC_STEP_1 ; 
 int CT_AGC_STOP ; 
 int /*<<< orphan*/  CT_DEMOD_START ; 
 int CT_SHUTDOWN ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int dib0090_gain_control (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_get_current_gain (struct dvb_frontend*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int dib0090_get_tune_state (struct dvb_frontend*) ; 
 int dib0090_get_wbd_offset (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_pwm_gain_reset (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_set_tune_state (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_pwm_agc_reset (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib8000_set_gpio (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib8000_set_tune_state (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_set_wbd_ref (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 

__attribute__((used)) static int dib8096_set_param_override(struct dvb_frontend *fe,
		struct dvb_frontend_parameters *fep)
{
    struct dvb_usb_adapter *adap = fe->dvb->priv;
    struct dib0700_adapter_state *state = adap->priv;
    u8 band = BAND_OF_FREQUENCY(fep->frequency/1000);
    u16 offset;
    int ret = 0;
    enum frontend_tune_state tune_state = CT_SHUTDOWN;
    u16 ltgain, rf_gain_limit;

    ret = state->set_param_save(fe, fep);
    if (ret < 0)
	return ret;

    switch (band) {
    case BAND_VHF:
	    offset = 100;
	    break;
    case BAND_UHF:
	    offset = 550;
	    break;
    default:
	    offset = 0;
	    break;
    }
    offset += (dib0090_get_wbd_offset(fe) * 8 * 18 / 33 + 1) / 2;
    dib8000_set_wbd_ref(fe, offset);


    if (band == BAND_CBAND) {
	deb_info("tuning in CBAND - soft-AGC startup\n");
	/* TODO specific wbd target for dib0090 - needed for startup ? */
	dib0090_set_tune_state(fe, CT_AGC_START);
	do {
		ret = dib0090_gain_control(fe);
		msleep(ret);
		tune_state = dib0090_get_tune_state(fe);
		if (tune_state == CT_AGC_STEP_0)
			dib8000_set_gpio(fe, 6, 0, 1);
		else if (tune_state == CT_AGC_STEP_1) {
			dib0090_get_current_gain(fe, NULL, NULL, &rf_gain_limit, &ltgain);
			if (rf_gain_limit == 0)
				dib8000_set_gpio(fe, 6, 0, 0);
		}
	} while (tune_state < CT_AGC_STOP);
	dib0090_pwm_gain_reset(fe);
	dib8000_pwm_agc_reset(fe);
	dib8000_set_tune_state(fe, CT_DEMOD_START);
    } else {
	deb_info("not tuning in CBAND - standard AGC startup\n");
	dib0090_pwm_gain_reset(fe);
    }

    return 0;
}