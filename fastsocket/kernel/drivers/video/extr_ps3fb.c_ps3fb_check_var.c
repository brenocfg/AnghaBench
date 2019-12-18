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
struct TYPE_9__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_8__ {scalar_t__ offset; int length; scalar_t__ msb_right; } ;
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int xres_virtual; int xoffset; int xres; int yoffset; int yres; int yres_virtual; int bits_per_pixel; int height; int width; scalar_t__ rotate; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; scalar_t__ nonstd; scalar_t__ grayscale; } ;
struct TYPE_10__ {int smem_len; } ;
struct fb_info {int /*<<< orphan*/  device; TYPE_5__ fix; } ;

/* Variables and functions */
 int BPP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int ps3fb_find_mode (struct fb_var_screeninfo*,int*,int*) ; 

__attribute__((used)) static int ps3fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	u32 xdr_line_length, ddr_line_length;
	int mode;

	mode = ps3fb_find_mode(var, &ddr_line_length, &xdr_line_length);
	if (!mode)
		return -EINVAL;

	/* Virtual screen */
	if (var->xres_virtual > xdr_line_length / BPP) {
		dev_dbg(info->device,
			"Horizontal virtual screen size too large\n");
		return -EINVAL;
	}

	if (var->xoffset + var->xres > var->xres_virtual ||
	    var->yoffset + var->yres > var->yres_virtual) {
		dev_dbg(info->device, "panning out-of-range\n");
		return -EINVAL;
	}

	/* We support ARGB8888 only */
	if (var->bits_per_pixel > 32 || var->grayscale ||
	    var->red.offset > 16 || var->green.offset > 8 ||
	    var->blue.offset > 0 || var->transp.offset > 24 ||
	    var->red.length > 8 || var->green.length > 8 ||
	    var->blue.length > 8 || var->transp.length > 8 ||
	    var->red.msb_right || var->green.msb_right ||
	    var->blue.msb_right || var->transp.msb_right || var->nonstd) {
		dev_dbg(info->device, "We support ARGB8888 only\n");
		return -EINVAL;
	}

	var->bits_per_pixel = 32;
	var->red.offset = 16;
	var->green.offset = 8;
	var->blue.offset = 0;
	var->transp.offset = 24;
	var->red.length = 8;
	var->green.length = 8;
	var->blue.length = 8;
	var->transp.length = 8;
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	/* Rotation is not supported */
	if (var->rotate) {
		dev_dbg(info->device, "Rotation is not supported\n");
		return -EINVAL;
	}

	/* Memory limit */
	if (var->yres_virtual * xdr_line_length > info->fix.smem_len) {
		dev_dbg(info->device, "Not enough memory\n");
		return -ENOMEM;
	}

	var->height = -1;
	var->width = -1;

	return 0;
}