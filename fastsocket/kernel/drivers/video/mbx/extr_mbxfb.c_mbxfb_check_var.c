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
struct pixclock_div {int dummy; } ;
struct TYPE_8__ {int length; int offset; scalar_t__ msb_right; } ;
struct TYPE_7__ {int length; scalar_t__ msb_right; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int length; int offset; scalar_t__ msb_right; } ;
struct TYPE_5__ {int length; int offset; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; int bits_per_pixel; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; void* yres_virtual; void* xres_virtual; int /*<<< orphan*/  pixclock; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_XRES ; 
 scalar_t__ MAX_YRES ; 
 scalar_t__ MIN_XRES ; 
 scalar_t__ MIN_YRES ; 
 void* max (void*,scalar_t__) ; 
 int /*<<< orphan*/  mbxfb_get_pixclock (int /*<<< orphan*/ ,struct pixclock_div*) ; 

__attribute__((used)) static int mbxfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct pixclock_div div;

	var->pixclock = mbxfb_get_pixclock(var->pixclock, &div);

	if (var->xres < MIN_XRES)
		var->xres = MIN_XRES;
	if (var->yres < MIN_YRES)
		var->yres = MIN_YRES;
	if (var->xres > MAX_XRES)
		return -EINVAL;
	if (var->yres > MAX_YRES)
		return -EINVAL;
	var->xres_virtual = max(var->xres_virtual, var->xres);
	var->yres_virtual = max(var->yres_virtual, var->yres);

	switch (var->bits_per_pixel) {
		/* 8 bits-per-pixel is not supported yet */
	case 8:
		return -EINVAL;
	case 16:
		var->green.length = (var->green.length == 5) ? 5 : 6;
		var->red.length = 5;
		var->blue.length = 5;
		var->transp.length = 6 - var->green.length;
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 5 + var->green.length;
		var->transp.offset = (5 + var->red.offset) & 15;
		break;
	case 24:		/* RGB 888   */
	case 32:		/* RGBA 8888 */
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.length = var->bits_per_pixel - 24;
		var->transp.offset = (var->transp.length) ? 24 : 0;
		break;
	}
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	return 0;
}