#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct s3c2410fb_mach_info {unsigned int num_displays; struct s3c2410fb_display* displays; int /*<<< orphan*/  default_display; } ;
struct TYPE_6__ {int lcdcon5; int lcdcon1; } ;
struct s3c2410fb_info {TYPE_2__ regs; TYPE_1__* dev; } ;
struct s3c2410fb_display {int type; scalar_t__ yres; scalar_t__ xres; scalar_t__ bpp; int lcdcon5; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_8__ {int offset; scalar_t__ length; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ offset; } ;
struct fb_var_screeninfo {scalar_t__ yres; scalar_t__ xres; scalar_t__ bits_per_pixel; scalar_t__ xres_virtual; scalar_t__ yres_virtual; TYPE_4__ blue; TYPE_4__ green; TYPE_4__ red; TYPE_3__ transp; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct fb_info {struct s3c2410fb_info* par; } ;
struct TYPE_5__ {struct s3c2410fb_mach_info* platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int S3C2410_LCDCON1_TFT ; 
 int S3C2410_LCDCON5_FRM565 ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static int s3c2410fb_check_var(struct fb_var_screeninfo *var,
			       struct fb_info *info)
{
	struct s3c2410fb_info *fbi = info->par;
	struct s3c2410fb_mach_info *mach_info = fbi->dev->platform_data;
	struct s3c2410fb_display *display = NULL;
	struct s3c2410fb_display *default_display = mach_info->displays +
						    mach_info->default_display;
	int type = default_display->type;
	unsigned i;

	dprintk("check_var(var=%p, info=%p)\n", var, info);

	/* validate x/y resolution */
	/* choose default mode if possible */
	if (var->yres == default_display->yres &&
	    var->xres == default_display->xres &&
	    var->bits_per_pixel == default_display->bpp)
		display = default_display;
	else
		for (i = 0; i < mach_info->num_displays; i++)
			if (type == mach_info->displays[i].type &&
			    var->yres == mach_info->displays[i].yres &&
			    var->xres == mach_info->displays[i].xres &&
			    var->bits_per_pixel == mach_info->displays[i].bpp) {
				display = mach_info->displays + i;
				break;
			}

	if (!display) {
		dprintk("wrong resolution or depth %dx%d at %d bpp\n",
			var->xres, var->yres, var->bits_per_pixel);
		return -EINVAL;
	}

	/* it is always the size as the display */
	var->xres_virtual = display->xres;
	var->yres_virtual = display->yres;
	var->height = display->height;
	var->width = display->width;

	/* copy lcd settings */
	var->pixclock = display->pixclock;
	var->left_margin = display->left_margin;
	var->right_margin = display->right_margin;
	var->upper_margin = display->upper_margin;
	var->lower_margin = display->lower_margin;
	var->vsync_len = display->vsync_len;
	var->hsync_len = display->hsync_len;

	fbi->regs.lcdcon5 = display->lcdcon5;
	/* set display type */
	fbi->regs.lcdcon1 = display->type;

	var->transp.offset = 0;
	var->transp.length = 0;
	/* set r/g/b positions */
	switch (var->bits_per_pixel) {
	case 1:
	case 2:
	case 4:
		var->red.offset	= 0;
		var->red.length	= var->bits_per_pixel;
		var->green	= var->red;
		var->blue	= var->red;
		break;
	case 8:
		if (display->type != S3C2410_LCDCON1_TFT) {
			/* 8 bpp 332 */
			var->red.length		= 3;
			var->red.offset		= 5;
			var->green.length	= 3;
			var->green.offset	= 2;
			var->blue.length	= 2;
			var->blue.offset	= 0;
		} else {
			var->red.offset		= 0;
			var->red.length		= 8;
			var->green		= var->red;
			var->blue		= var->red;
		}
		break;
	case 12:
		/* 12 bpp 444 */
		var->red.length		= 4;
		var->red.offset		= 8;
		var->green.length	= 4;
		var->green.offset	= 4;
		var->blue.length	= 4;
		var->blue.offset	= 0;
		break;

	default:
	case 16:
		if (display->lcdcon5 & S3C2410_LCDCON5_FRM565) {
			/* 16 bpp, 565 format */
			var->red.offset		= 11;
			var->green.offset	= 5;
			var->blue.offset	= 0;
			var->red.length		= 5;
			var->green.length	= 6;
			var->blue.length	= 5;
		} else {
			/* 16 bpp, 5551 format */
			var->red.offset		= 11;
			var->green.offset	= 6;
			var->blue.offset	= 1;
			var->red.length		= 5;
			var->green.length	= 5;
			var->blue.length	= 5;
		}
		break;
	case 32:
		/* 24 bpp 888 and 8 dummy */
		var->red.length		= 8;
		var->red.offset		= 16;
		var->green.length	= 8;
		var->green.offset	= 8;
		var->blue.length	= 8;
		var->blue.offset	= 0;
		break;
	}
	return 0;
}