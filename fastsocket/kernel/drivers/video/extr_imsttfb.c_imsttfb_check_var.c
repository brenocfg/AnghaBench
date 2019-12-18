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
struct TYPE_8__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_7__ {int length; scalar_t__ msb_right; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_10__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; int xres; int yres_virtual; int yres; int vmode; int height; int width; int left_margin; int right_margin; int upper_margin; int lower_margin; int hsync_len; int vsync_len; TYPE_3__ transp; TYPE_2__ blue; TYPE_1__ green; TYPE_5__ red; scalar_t__ nonstd; } ;
struct TYPE_9__ {int smem_len; } ;
struct fb_info {TYPE_4__ fix; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 
 int PAGE_SIZE ; 

__attribute__((used)) static int
imsttfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	if ((var->bits_per_pixel != 8 && var->bits_per_pixel != 16
	    && var->bits_per_pixel != 24 && var->bits_per_pixel != 32)
	    || var->xres_virtual < var->xres || var->yres_virtual < var->yres
	    || var->nonstd
	    || (var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		return -EINVAL;

	if ((var->xres * var->yres) * (var->bits_per_pixel >> 3) > info->fix.smem_len
	    || (var->xres_virtual * var->yres_virtual) * (var->bits_per_pixel >> 3) > info->fix.smem_len)
		return -EINVAL;

	switch (var->bits_per_pixel) {
		case 8:
			var->red.offset = 0;
			var->red.length = 8;
			var->green.offset = 0;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 0;
			var->transp.length = 0;
			break;
		case 16:	/* RGB 555 or 565 */
			if (var->green.length != 6)
				var->red.offset = 10;
			var->red.length = 5;
			var->green.offset = 5;
			if (var->green.length != 6)
				var->green.length = 5;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
			break;
		case 24:	/* RGB 888 */
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 0;
			var->transp.length = 0;
			break;
		case 32:	/* RGBA 8888 */
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 24;
			var->transp.length = 8;
			break;
	}

	if (var->yres == var->yres_virtual) {
		__u32 vram = (info->fix.smem_len - (PAGE_SIZE << 2));
		var->yres_virtual = ((vram << 3) / var->bits_per_pixel) / var->xres_virtual;
		if (var->yres_virtual < var->yres)
			var->yres_virtual = var->yres;
	}

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;
	var->height = -1;
	var->width = -1;
	var->vmode = FB_VMODE_NONINTERLACED;
	var->left_margin = var->right_margin = 16;
	var->upper_margin = var->lower_margin = 16;
	var->hsync_len = var->vsync_len = 8;
	return 0;
}