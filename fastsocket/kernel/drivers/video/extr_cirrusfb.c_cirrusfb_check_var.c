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
struct TYPE_4__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_3__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; scalar_t__ xres_virtual; scalar_t__ xres; int yres_virtual; scalar_t__ yres; scalar_t__ xoffset; scalar_t__ yoffset; int vmode; int /*<<< orphan*/  accel_flags; TYPE_2__ transp; TYPE_1__ blue; TYPE_1__ green; TYPE_1__ red; } ;
struct fb_info {int screen_size; int /*<<< orphan*/  device; struct cirrusfb_info* par; } ;
struct cirrusfb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 scalar_t__ cirrusfb_check_pixclock (struct fb_var_screeninfo*,struct fb_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  isPReP ; 
 int /*<<< orphan*/  is_laguna (struct cirrusfb_info*) ; 

__attribute__((used)) static int cirrusfb_check_var(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	int yres;
	/* memory size in pixels */
	unsigned pixels = info->screen_size * 8 / var->bits_per_pixel;
	struct cirrusfb_info *cinfo = info->par;

	switch (var->bits_per_pixel) {
	case 1:
		var->red.offset = 0;
		var->red.length = 1;
		var->green = var->red;
		var->blue = var->red;
		break;

	case 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green = var->red;
		var->blue = var->red;
		break;

	case 16:
		if (isPReP) {
			var->red.offset = 2;
			var->green.offset = -3;
			var->blue.offset = 8;
		} else {
			var->red.offset = 11;
			var->green.offset = 5;
			var->blue.offset = 0;
		}
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		break;

	case 24:
		if (isPReP) {
			var->red.offset = 0;
			var->green.offset = 8;
			var->blue.offset = 16;
		} else {
			var->red.offset = 16;
			var->green.offset = 8;
			var->blue.offset = 0;
		}
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;

	default:
		dev_dbg(info->device,
			"Unsupported bpp size: %d\n", var->bits_per_pixel);
		return -EINVAL;
	}

	if (var->xres_virtual < var->xres)
		var->xres_virtual = var->xres;
	/* use highest possible virtual resolution */
	if (var->yres_virtual == -1) {
		var->yres_virtual = pixels / var->xres_virtual;

		dev_info(info->device,
			 "virtual resolution set to maximum of %dx%d\n",
			 var->xres_virtual, var->yres_virtual);
	}
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;

	if (var->xres_virtual * var->yres_virtual > pixels) {
		dev_err(info->device, "mode %dx%dx%d rejected... "
		      "virtual resolution too high to fit into video memory!\n",
			var->xres_virtual, var->yres_virtual,
			var->bits_per_pixel);
		return -EINVAL;
	}

	if (var->xoffset < 0)
		var->xoffset = 0;
	if (var->yoffset < 0)
		var->yoffset = 0;

	/* truncate xoffset and yoffset to maximum if too high */
	if (var->xoffset > var->xres_virtual - var->xres)
		var->xoffset = var->xres_virtual - var->xres - 1;
	if (var->yoffset > var->yres_virtual - var->yres)
		var->yoffset = var->yres_virtual - var->yres - 1;

	var->red.msb_right =
	    var->green.msb_right =
	    var->blue.msb_right =
	    var->transp.offset =
	    var->transp.length =
	    var->transp.msb_right = 0;

	yres = var->yres;
	if (var->vmode & FB_VMODE_DOUBLE)
		yres *= 2;
	else if (var->vmode & FB_VMODE_INTERLACED)
		yres = (yres + 1) / 2;

	if (yres >= 1280) {
		dev_err(info->device, "ERROR: VerticalTotal >= 1280; "
			"special treatment required! (TODO)\n");
		return -EINVAL;
	}

	if (cirrusfb_check_pixclock(var, info))
		return -EINVAL;

	if (!is_laguna(cinfo))
		var->accel_flags = FB_ACCELF_TEXT;

	return 0;
}