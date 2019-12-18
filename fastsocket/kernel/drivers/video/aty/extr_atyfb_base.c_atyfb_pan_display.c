#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct fb_var_screeninfo {int xoffset; int yoffset; int activate; } ;
struct TYPE_4__ {int xoffset; int yoffset; } ;
struct fb_info {TYPE_1__ var; scalar_t__ par; } ;
struct TYPE_6__ {int h_tot_disp; int v_tot_disp; int gen_cntl; int vxres; int vyres; int /*<<< orphan*/  off_pitch; } ;
struct TYPE_5__ {int pan_display; } ;
struct atyfb_par {TYPE_3__ crtc; TYPE_2__ vblank; scalar_t__ asleep; } ;

/* Variables and functions */
 int CRTC_DBL_SCAN_EN ; 
 int /*<<< orphan*/  CRTC_OFF_PITCH ; 
 int EINVAL ; 
 int FB_ACTIVATE_VBL ; 
 int /*<<< orphan*/  aty_enable_irq (struct atyfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  set_off_pitch (struct atyfb_par*,struct fb_info*) ; 

__attribute__((used)) static int atyfb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 xres, yres, xoffset, yoffset;

	xres = (((par->crtc.h_tot_disp >> 16) & 0xff) + 1) * 8;
	yres = ((par->crtc.v_tot_disp >> 16) & 0x7ff) + 1;
	if (par->crtc.gen_cntl & CRTC_DBL_SCAN_EN)
		yres >>= 1;
	xoffset = (var->xoffset + 7) & ~7;
	yoffset = var->yoffset;
	if (xoffset + xres > par->crtc.vxres ||
	    yoffset + yres > par->crtc.vyres)
		return -EINVAL;
	info->var.xoffset = xoffset;
	info->var.yoffset = yoffset;
	if (par->asleep)
		return 0;

	set_off_pitch(par, info);
	if ((var->activate & FB_ACTIVATE_VBL) && !aty_enable_irq(par, 0)) {
		par->vblank.pan_display = 1;
	} else {
		par->vblank.pan_display = 0;
		aty_st_le32(CRTC_OFF_PITCH, par->crtc.off_pitch, par);
	}

	return 0;
}