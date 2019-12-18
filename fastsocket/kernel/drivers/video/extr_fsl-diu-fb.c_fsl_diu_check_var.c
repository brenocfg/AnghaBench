#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; int offset; int /*<<< orphan*/  msb_right; } ;
struct TYPE_8__ {int length; int offset; int /*<<< orphan*/  msb_right; } ;
struct TYPE_7__ {int length; int offset; int /*<<< orphan*/  msb_right; } ;
struct TYPE_10__ {int length; int offset; int /*<<< orphan*/  msb_right; } ;
struct fb_var_screeninfo {unsigned long xres; unsigned long yres; unsigned long xres_virtual; unsigned long yres_virtual; scalar_t__ xoffset; scalar_t__ yoffset; int bits_per_pixel; unsigned long pixclock; unsigned long right_margin; unsigned long hsync_len; unsigned long left_margin; unsigned long lower_margin; unsigned long vsync_len; unsigned long upper_margin; int height; int width; int /*<<< orphan*/  sync; int /*<<< orphan*/  nonstd; scalar_t__ grayscale; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_5__ red; } ;
struct TYPE_6__ {scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 unsigned long KHZ2PICOS (unsigned long) ; 
 unsigned long MAX_PIX_CLK ; 
 unsigned long MIN_PIX_CLK ; 
 int /*<<< orphan*/  adjust_aoi_size_position (struct fb_var_screeninfo*,struct fb_info*) ; 
 int default_bpp ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 

__attribute__((used)) static int fsl_diu_check_var(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	unsigned long htotal, vtotal;

	pr_debug("check_var xres: %d\n", var->xres);
	pr_debug("check_var yres: %d\n", var->yres);

	if (var->xres_virtual < var->xres)
		var->xres_virtual = var->xres;
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;

	if (var->xoffset < 0)
		var->xoffset = 0;

	if (var->yoffset < 0)
		var->yoffset = 0;

	if (var->xoffset + info->var.xres > info->var.xres_virtual)
		var->xoffset = info->var.xres_virtual - info->var.xres;

	if (var->yoffset + info->var.yres > info->var.yres_virtual)
		var->yoffset = info->var.yres_virtual - info->var.yres;

	if ((var->bits_per_pixel != 32) && (var->bits_per_pixel != 24) &&
	    (var->bits_per_pixel != 16))
		var->bits_per_pixel = default_bpp;

	switch (var->bits_per_pixel) {
	case 16:
		var->red.length = 5;
		var->red.offset = 11;
		var->red.msb_right = 0;

		var->green.length = 6;
		var->green.offset = 5;
		var->green.msb_right = 0;

		var->blue.length = 5;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 0;
		var->transp.offset = 0;
		var->transp.msb_right = 0;
		break;
	case 24:
		var->red.length = 8;
		var->red.offset = 0;
		var->red.msb_right = 0;

		var->green.length = 8;
		var->green.offset = 8;
		var->green.msb_right = 0;

		var->blue.length = 8;
		var->blue.offset = 16;
		var->blue.msb_right = 0;

		var->transp.length = 0;
		var->transp.offset = 0;
		var->transp.msb_right = 0;
		break;
	case 32:
		var->red.length = 8;
		var->red.offset = 16;
		var->red.msb_right = 0;

		var->green.length = 8;
		var->green.offset = 8;
		var->green.msb_right = 0;

		var->blue.length = 8;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 8;
		var->transp.offset = 24;
		var->transp.msb_right = 0;

		break;
	}
	/* If the pixclock is below the minimum spec'd value then set to
	 * refresh rate for 60Hz since this is supported by most monitors.
	 * Refer to Documentation/fb/ for calculations.
	 */
	if ((var->pixclock < MIN_PIX_CLK) || (var->pixclock > MAX_PIX_CLK)) {
		htotal = var->xres + var->right_margin + var->hsync_len +
		    var->left_margin;
		vtotal = var->yres + var->lower_margin + var->vsync_len +
		    var->upper_margin;
		var->pixclock = (vtotal * htotal * 6UL) / 100UL;
		var->pixclock = KHZ2PICOS(var->pixclock);
		pr_debug("pixclock set for 60Hz refresh = %u ps\n",
			var->pixclock);
	}

	var->height = -1;
	var->width = -1;
	var->grayscale = 0;

	/* Copy nonstd field to/from sync for fbset usage */
	var->sync |= var->nonstd;
	var->nonstd |= var->sync;

	adjust_aoi_size_position(var, info);
	return 0;
}