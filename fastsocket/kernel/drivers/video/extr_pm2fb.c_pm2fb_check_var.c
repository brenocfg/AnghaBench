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
struct TYPE_10__ {int length; int offset; } ;
struct TYPE_9__ {int length; int offset; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int xres_virtual; int yres; int yres_virtual; int vmode; int height; int width; scalar_t__ accel_flags; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; TYPE_2__ transp; int /*<<< orphan*/  pixclock; scalar_t__ xoffset; } ;
struct TYPE_6__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 
 int /*<<< orphan*/  PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM2_MAX_PIXCLOCK ; 

__attribute__((used)) static int pm2fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	u32 lpitch;

	if (var->bits_per_pixel != 8  && var->bits_per_pixel != 16 &&
	    var->bits_per_pixel != 24 && var->bits_per_pixel != 32) {
		DPRINTK("depth not supported: %u\n", var->bits_per_pixel);
		return -EINVAL;
	}

	if (var->xres != var->xres_virtual) {
		DPRINTK("virtual x resolution != "
			"physical x resolution not supported\n");
		return -EINVAL;
	}

	if (var->yres > var->yres_virtual) {
		DPRINTK("virtual y resolution < "
			"physical y resolution not possible\n");
		return -EINVAL;
	}

	/* permedia cannot blit over 2048 */
	if (var->yres_virtual > 2047) {
		var->yres_virtual = 2047;
	}

	if (var->xoffset) {
		DPRINTK("xoffset not supported\n");
		return -EINVAL;
	}

	if ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) {
		DPRINTK("interlace not supported\n");
		return -EINVAL;
	}

	var->xres = (var->xres + 15) & ~15; /* could sometimes be 8 */
	lpitch = var->xres * ((var->bits_per_pixel + 7) >> 3);

	if (var->xres < 320 || var->xres > 1600) {
		DPRINTK("width not supported: %u\n", var->xres);
		return -EINVAL;
	}

	if (var->yres < 200 || var->yres > 1200) {
		DPRINTK("height not supported: %u\n", var->yres);
		return -EINVAL;
	}

	if (lpitch * var->yres_virtual > info->fix.smem_len) {
		DPRINTK("no memory for screen (%ux%ux%u)\n",
			var->xres, var->yres_virtual, var->bits_per_pixel);
		return -EINVAL;
	}

	if (PICOS2KHZ(var->pixclock) > PM2_MAX_PIXCLOCK) {
		DPRINTK("pixclock too high (%ldKHz)\n",
			PICOS2KHZ(var->pixclock));
		return -EINVAL;
	}

	var->transp.offset = 0;
	var->transp.length = 0;
	switch (var->bits_per_pixel) {
	case 8:
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	case 16:
		var->red.offset   = 11;
		var->red.length   = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset  = 0;
		var->blue.length  = 5;
		break;
	case 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset	  = 16;
		var->green.offset = 8;
		var->blue.offset  = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	case 24:
#ifdef __BIG_ENDIAN
		var->red.offset   = 0;
		var->blue.offset  = 16;
#else
		var->red.offset   = 16;
		var->blue.offset  = 0;
#endif
		var->green.offset = 8;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	}
	var->height = -1;
	var->width = -1;

	var->accel_flags = 0;	/* Can't mmap if this is on */

	DPRINTK("Checking graphics mode at %dx%d depth %d\n",
		var->xres, var->yres, var->bits_per_pixel);
	return 0;
}