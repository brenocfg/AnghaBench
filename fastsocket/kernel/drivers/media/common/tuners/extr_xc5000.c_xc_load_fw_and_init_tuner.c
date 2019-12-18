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
struct xc5000_priv {int dummy; } ;
struct dvb_frontend {struct xc5000_priv* tuner_priv; } ;

/* Variables and functions */
 int XC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  XC_RF_MODE_CABLE ; 
 int /*<<< orphan*/  XREG_SIGNALSOURCE ; 
 int xc5000_fwupload (struct dvb_frontend*) ; 
 int xc5000_is_firmware_loaded (struct dvb_frontend*) ; 
 int xc_initialize (struct xc5000_priv*) ; 
 int /*<<< orphan*/  xc_wait (int) ; 
 int xc_write_reg (struct xc5000_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xc_load_fw_and_init_tuner(struct dvb_frontend *fe)
{
	struct xc5000_priv *priv = fe->tuner_priv;
	int ret = 0;

	if (xc5000_is_firmware_loaded(fe) != XC_RESULT_SUCCESS) {
		ret = xc5000_fwupload(fe);
		if (ret != XC_RESULT_SUCCESS)
			return ret;
	}

	/* Start the tuner self-calibration process */
	ret |= xc_initialize(priv);

	/* Wait for calibration to complete.
	 * We could continue but XC5000 will clock stretch subsequent
	 * I2C transactions until calibration is complete.  This way we
	 * don't have to rely on clock stretching working.
	 */
	xc_wait(100);

	/* Default to "CABLE" mode */
	ret |= xc_write_reg(priv, XREG_SIGNALSOURCE, XC_RF_MODE_CABLE);

	return ret;
}