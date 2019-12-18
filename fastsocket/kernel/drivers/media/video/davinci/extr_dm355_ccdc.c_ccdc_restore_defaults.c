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
struct TYPE_3__ {void* b_mg; void* gr_cy; void* gb_g; void* r_ye; } ;
struct TYPE_4__ {TYPE_1__ gain; } ;

/* Variables and functions */
 int CCDC_REG_LAST ; 
 int CULH ; 
 int /*<<< orphan*/  CULH_DEFAULT ; 
 int CULV ; 
 int /*<<< orphan*/  CULV_DEFAULT ; 
 int EFAULT ; 
 void* GAIN_DEFAULT ; 
 int LSCCFG2 ; 
 int /*<<< orphan*/  LSCCFG2_DEFAULT ; 
 int MODESET ; 
 int /*<<< orphan*/  MODESET_DEFAULT ; 
 int OUTCLIP ; 
 int /*<<< orphan*/  OUTCLIP_DEFAULT ; 
 int /*<<< orphan*/  VPSS_CCDCIN ; 
 int /*<<< orphan*/  VPSS_CCDC_CLOCK ; 
 int /*<<< orphan*/  ccdc_config_gain_offset () ; 
 TYPE_2__ ccdc_hw_params_raw ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regw (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vpss_enable_clock (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vpss_select_ccdc_source (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccdc_restore_defaults(void)
{
	int i;

	dev_dbg(dev, "\nstarting ccdc_restore_defaults...");
	/* set all registers to zero */
	for (i = 0; i <= CCDC_REG_LAST; i += 4)
		regw(0, i);

	/* now override the values with power on defaults in registers */
	regw(MODESET_DEFAULT, MODESET);
	/* no culling support */
	regw(CULH_DEFAULT, CULH);
	regw(CULV_DEFAULT, CULV);
	/* Set default Gain and Offset */
	ccdc_hw_params_raw.gain.r_ye = GAIN_DEFAULT;
	ccdc_hw_params_raw.gain.gb_g = GAIN_DEFAULT;
	ccdc_hw_params_raw.gain.gr_cy = GAIN_DEFAULT;
	ccdc_hw_params_raw.gain.b_mg = GAIN_DEFAULT;
	ccdc_config_gain_offset();
	regw(OUTCLIP_DEFAULT, OUTCLIP);
	regw(LSCCFG2_DEFAULT, LSCCFG2);
	/* select ccdc input */
	if (vpss_select_ccdc_source(VPSS_CCDCIN)) {
		dev_dbg(dev, "\ncouldn't select ccdc input source");
		return -EFAULT;
	}
	/* select ccdc clock */
	if (vpss_enable_clock(VPSS_CCDC_CLOCK, 1) < 0) {
		dev_dbg(dev, "\ncouldn't enable ccdc clock");
		return -EFAULT;
	}
	dev_dbg(dev, "\nEnd of ccdc_restore_defaults...");
	return 0;
}