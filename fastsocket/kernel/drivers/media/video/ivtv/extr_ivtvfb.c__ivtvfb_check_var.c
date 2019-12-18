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
typedef  int u32 ;
struct osd_info {int video_buffer_size; } ;
struct TYPE_6__ {int width; int height; } ;
struct ivtv {TYPE_1__ osd_rect; scalar_t__ is_50hz; struct osd_info* osd_info; } ;
struct TYPE_10__ {int offset; int length; } ;
struct TYPE_9__ {int length; scalar_t__ offset; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int yres; int xres_virtual; int yres_virtual; int xoffset; int yoffset; int nonstd; int vmode; int left_margin; int upper_margin; int right_margin; int lower_margin; int hsync_len; int vsync_len; int pixclock; TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  IVTVFB_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IVTVFB_DEBUG_WARN (char*,int,...) ; 
 int IVTV_OSD_MAX_WIDTH ; 

__attribute__((used)) static int _ivtvfb_check_var(struct fb_var_screeninfo *var, struct ivtv *itv)
{
	struct osd_info *oi = itv->osd_info;
	int osd_height_limit;
	u32 pixclock, hlimit, vlimit;

	IVTVFB_DEBUG_INFO("ivtvfb_check_var\n");

	/* Set base references for mode calcs. */
	if (itv->is_50hz) {
		pixclock = 84316;
		hlimit = 776;
		vlimit = 591;
		osd_height_limit = 576;
	}
	else {
		pixclock = 83926;
		hlimit = 776;
		vlimit = 495;
		osd_height_limit = 480;
	}

	if (var->bits_per_pixel == 8 || var->bits_per_pixel == 32) {
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
	}
	else if (var->bits_per_pixel == 16) {
		/* To find out the true mode, check green length */
		switch (var->green.length) {
			case 4:
				var->red.offset = 8;
				var->red.length = 4;
				var->green.offset = 4;
				var->green.length = 4;
				var->blue.offset = 0;
				var->blue.length = 4;
				var->transp.offset = 12;
				var->transp.length = 1;
				break;
			case 5:
				var->red.offset = 10;
				var->red.length = 5;
				var->green.offset = 5;
				var->green.length = 5;
				var->blue.offset = 0;
				var->blue.length = 5;
				var->transp.offset = 15;
				var->transp.length = 1;
				break;
			default:
				var->red.offset = 11;
				var->red.length = 5;
				var->green.offset = 5;
				var->green.length = 6;
				var->blue.offset = 0;
				var->blue.length = 5;
				var->transp.offset = 0;
				var->transp.length = 0;
				break;
		}
	}
	else {
		IVTVFB_DEBUG_WARN("Invalid colour mode: %d\n", var->bits_per_pixel);
		return -EINVAL;
	}

	/* Check the resolution */
	if (var->xres > IVTV_OSD_MAX_WIDTH || var->yres > osd_height_limit) {
		IVTVFB_DEBUG_WARN("Invalid resolution: %dx%d\n",
				var->xres, var->yres);
		return -EINVAL;
	}

	/* Max horizontal size is 1023 @ 32bpp, 2046 & 16bpp, 4092 @ 8bpp */
	if (var->xres_virtual > 4095 / (var->bits_per_pixel / 8) ||
	    var->xres_virtual * var->yres_virtual * (var->bits_per_pixel / 8) > oi->video_buffer_size ||
	    var->xres_virtual < var->xres ||
	    var->yres_virtual < var->yres) {
		IVTVFB_DEBUG_WARN("Invalid virtual resolution: %dx%d\n",
			var->xres_virtual, var->yres_virtual);
		return -EINVAL;
	}

	/* Some extra checks if in 8 bit mode */
	if (var->bits_per_pixel == 8) {
		/* Width must be a multiple of 4 */
		if (var->xres & 3) {
			IVTVFB_DEBUG_WARN("Invalid resolution for 8bpp: %d\n", var->xres);
			return -EINVAL;
		}
		if (var->xres_virtual & 3) {
			IVTVFB_DEBUG_WARN("Invalid virtual resolution for 8bpp: %d)\n", var->xres_virtual);
			return -EINVAL;
		}
	}
	else if (var->bits_per_pixel == 16) {
		/* Width must be a multiple of 2 */
		if (var->xres & 1) {
			IVTVFB_DEBUG_WARN("Invalid resolution for 16bpp: %d\n", var->xres);
			return -EINVAL;
		}
		if (var->xres_virtual & 1) {
			IVTVFB_DEBUG_WARN("Invalid virtual resolution for 16bpp: %d)\n", var->xres_virtual);
			return -EINVAL;
		}
	}

	/* Now check the offsets */
	if (var->xoffset >= var->xres_virtual || var->yoffset >= var->yres_virtual) {
		IVTVFB_DEBUG_WARN("Invalid offset: %d (%d) %d (%d)\n",
			var->xoffset, var->xres_virtual, var->yoffset, var->yres_virtual);
		return -EINVAL;
	}

	/* Check pixel format */
	if (var->nonstd > 1) {
		IVTVFB_DEBUG_WARN("Invalid nonstd % d\n", var->nonstd);
		return -EINVAL;
	}

	/* Check video mode */
	if (((var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED) &&
		((var->vmode & FB_VMODE_MASK) != FB_VMODE_INTERLACED)) {
		IVTVFB_DEBUG_WARN("Invalid video mode: %d\n", var->vmode & FB_VMODE_MASK);
		return -EINVAL;
	}

	/* Check the left & upper margins
	   If the margins are too large, just center the screen
	   (enforcing margins causes too many problems) */

	if (var->left_margin + var->xres > IVTV_OSD_MAX_WIDTH + 1) {
		var->left_margin = 1 + ((IVTV_OSD_MAX_WIDTH - var->xres) / 2);
	}
	if (var->upper_margin + var->yres > (itv->is_50hz ? 577 : 481)) {
		var->upper_margin = 1 + (((itv->is_50hz ? 576 : 480) - var->yres) / 2);
	}

	/* Maintain overall 'size' for a constant refresh rate */
	var->right_margin = hlimit - var->left_margin - var->xres;
	var->lower_margin = vlimit - var->upper_margin - var->yres;

	/* Fixed sync times */
	var->hsync_len = 24;
	var->vsync_len = 2;

	/* Non-interlaced / interlaced mode is used to switch the OSD filter
	   on or off. Adjust the clock timings to maintain a constant
	   vertical refresh rate. */
	if ((var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED)
		var->pixclock = pixclock / 2;
	else
		var->pixclock = pixclock;

	itv->osd_rect.width = var->xres;
	itv->osd_rect.height = var->yres;

	IVTVFB_DEBUG_INFO("Display size: %dx%d (virtual %dx%d) @ %dbpp\n",
		      var->xres, var->yres,
		      var->xres_virtual, var->yres_virtual,
		      var->bits_per_pixel);

	IVTVFB_DEBUG_INFO("Display position: %d, %d\n",
		      var->left_margin, var->upper_margin);

	IVTVFB_DEBUG_INFO("Display filter: %s\n",
			(var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED ? "on" : "off");
	IVTVFB_DEBUG_INFO("Color space: %s\n", var->nonstd ? "YUV" : "RGB");
	return 0;
}