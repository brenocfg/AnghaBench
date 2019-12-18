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
struct fb_var_screeninfo {int xres; int right_margin; int hsync_len; int left_margin; int yres; int lower_margin; int vsync_len; int upper_margin; int vmode; int /*<<< orphan*/  pixclock; } ;
struct TYPE_2__ {int hfmax; int vfmax; int dclkmax; int hfmin; int vfmin; int dclkmin; } ;
struct fb_info {TYPE_1__ monspecs; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 

int fb_validate_mode(const struct fb_var_screeninfo *var, struct fb_info *info)
{
	u32 hfreq, vfreq, htotal, vtotal, pixclock;
	u32 hfmin, hfmax, vfmin, vfmax, dclkmin, dclkmax;

	/*
	 * If monspecs are invalid, use values that are enough
	 * for 640x480@60
	 */
	if (!info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dclkmax ||
	    info->monspecs.hfmax < info->monspecs.hfmin ||
	    info->monspecs.vfmax < info->monspecs.vfmin ||
	    info->monspecs.dclkmax < info->monspecs.dclkmin) {
		hfmin = 29000; hfmax = 30000;
		vfmin = 60; vfmax = 60;
		dclkmin = 0; dclkmax = 25000000;
	} else {
		hfmin = info->monspecs.hfmin;
		hfmax = info->monspecs.hfmax;
		vfmin = info->monspecs.vfmin;
		vfmax = info->monspecs.vfmax;
		dclkmin = info->monspecs.dclkmin;
		dclkmax = info->monspecs.dclkmax;
	}

	if (!var->pixclock)
		return -EINVAL;
	pixclock = PICOS2KHZ(var->pixclock) * 1000;

	htotal = var->xres + var->right_margin + var->hsync_len +
		var->left_margin;
	vtotal = var->yres + var->lower_margin + var->vsync_len +
		var->upper_margin;

	if (var->vmode & FB_VMODE_INTERLACED)
		vtotal /= 2;
	if (var->vmode & FB_VMODE_DOUBLE)
		vtotal *= 2;

	hfreq = pixclock/htotal;
	hfreq = (hfreq + 500) / 1000 * 1000;

	vfreq = hfreq/vtotal;

	return (vfreq < vfmin || vfreq > vfmax ||
		hfreq < hfmin || hfreq > hfmax ||
		pixclock < dclkmin || pixclock > dclkmax) ?
		-EINVAL : 0;
}