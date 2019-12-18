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
struct msmfb_info {struct msm_panel_data* panel; } ;
struct msm_panel_data {int caps; } ;
struct fb_var_screeninfo {int* reserved; int /*<<< orphan*/  yoffset; } ;
struct TYPE_2__ {int xres; int yres; } ;
struct fb_info {TYPE_1__ var; struct msmfb_info* par; } ;

/* Variables and functions */
 int MSMFB_CAP_PARTIAL_UPDATES ; 
 int /*<<< orphan*/  msmfb_pan_update (struct fb_info*,int,int,int,int,int /*<<< orphan*/ ,int) ; 

int msmfb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct msmfb_info *msmfb = info->par;
	struct msm_panel_data *panel = msmfb->panel;

	/* "UPDT" */
	if ((panel->caps & MSMFB_CAP_PARTIAL_UPDATES) &&
	    (var->reserved[0] == 0x54445055)) {
		msmfb_pan_update(info, var->reserved[1] & 0xffff,
				 var->reserved[1] >> 16,
				 var->reserved[2] & 0xffff,
				 var->reserved[2] >> 16, var->yoffset, 1);
	} else {
		msmfb_pan_update(info, 0, 0, info->var.xres, info->var.yres,
				 var->yoffset, 1);
	}
	return 0;
}