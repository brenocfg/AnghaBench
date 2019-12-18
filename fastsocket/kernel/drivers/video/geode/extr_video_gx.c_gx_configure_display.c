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
typedef  int u32 ;
struct gxfb_par {scalar_t__ enable_crt; } ;
struct TYPE_2__ {int sync; } ;
struct fb_info {TYPE_1__ var; struct gxfb_par* par; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  VP_DCFG ; 
 int VP_DCFG_CRT_EN ; 
 int VP_DCFG_CRT_HSYNC_POL ; 
 int VP_DCFG_CRT_SYNC_SKW ; 
 int VP_DCFG_CRT_SYNC_SKW_DEFAULT ; 
 int VP_DCFG_CRT_VSYNC_POL ; 
 int VP_DCFG_DAC_BL_EN ; 
 int VP_DCFG_HSYNC_EN ; 
 int VP_DCFG_VSYNC_EN ; 
 int /*<<< orphan*/  VP_MISC ; 
 int VP_MISC_APWRDN ; 
 int VP_MISC_DACPWRDN ; 
 int VP_MISC_GAM_EN ; 
 int /*<<< orphan*/  gx_configure_tft (struct fb_info*) ; 
 int read_vp (struct gxfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_vp (struct gxfb_par*,int /*<<< orphan*/ ,int) ; 

void gx_configure_display(struct fb_info *info)
{
	struct gxfb_par *par = info->par;
	u32 dcfg, misc;

	/* Write the display configuration */
	dcfg = read_vp(par, VP_DCFG);

	/* Disable hsync and vsync */
	dcfg &= ~(VP_DCFG_VSYNC_EN | VP_DCFG_HSYNC_EN);
	write_vp(par, VP_DCFG, dcfg);

	/* Clear bits from existing mode. */
	dcfg &= ~(VP_DCFG_CRT_SYNC_SKW
		  | VP_DCFG_CRT_HSYNC_POL   | VP_DCFG_CRT_VSYNC_POL
		  | VP_DCFG_VSYNC_EN        | VP_DCFG_HSYNC_EN);

	/* Set default sync skew.  */
	dcfg |= VP_DCFG_CRT_SYNC_SKW_DEFAULT;

	/* Enable hsync and vsync. */
	dcfg |= VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN;

	misc = read_vp(par, VP_MISC);

	/* Disable gamma correction */
	misc |= VP_MISC_GAM_EN;

	if (par->enable_crt) {

		/* Power up the CRT DACs */
		misc &= ~(VP_MISC_APWRDN | VP_MISC_DACPWRDN);
		write_vp(par, VP_MISC, misc);

		/* Only change the sync polarities if we are running
		 * in CRT mode.  The FP polarities will be handled in
		 * gxfb_configure_tft */
		if (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
			dcfg |= VP_DCFG_CRT_HSYNC_POL;
		if (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
			dcfg |= VP_DCFG_CRT_VSYNC_POL;
	} else {
		/* Power down the CRT DACs if in FP mode */
		misc |= (VP_MISC_APWRDN | VP_MISC_DACPWRDN);
		write_vp(par, VP_MISC, misc);
	}

	/* Enable the display logic */
	/* Set up the DACS to blank normally */

	dcfg |= VP_DCFG_CRT_EN | VP_DCFG_DAC_BL_EN;

	/* Enable the external DAC VREF? */

	write_vp(par, VP_DCFG, dcfg);

	/* Set up the flat panel (if it is enabled) */

	if (par->enable_crt == 0)
		gx_configure_tft(info);
}