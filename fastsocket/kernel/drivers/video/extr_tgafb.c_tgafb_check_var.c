#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tga_par {scalar_t__ tga_type; } ;
struct TYPE_6__ {int length; scalar_t__ offset; } ;
struct TYPE_5__ {int length; int offset; } ;
struct TYPE_4__ {int length; int offset; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; int xres; scalar_t__ yres_virtual; scalar_t__ yres; int pixclock; int vmode; scalar_t__ nonstd; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 
 int TGA_PLL_MAX_FREQ ; 
 scalar_t__ TGA_TYPE_8PLANE ; 

__attribute__((used)) static int
tgafb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct tga_par *par = (struct tga_par *)info->par;

	if (par->tga_type == TGA_TYPE_8PLANE) {
		if (var->bits_per_pixel != 8)
			return -EINVAL;
	} else {
		if (var->bits_per_pixel != 32)
			return -EINVAL;
	}
	var->red.length = var->green.length = var->blue.length = 8;
	if (var->bits_per_pixel == 32) {
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
	}

	if (var->xres_virtual != var->xres || var->yres_virtual != var->yres)
		return -EINVAL;
	if (var->nonstd)
		return -EINVAL;
	if (1000000000 / var->pixclock > TGA_PLL_MAX_FREQ)
		return -EINVAL;
	if ((var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		return -EINVAL;

	/* Some of the acceleration routines assume the line width is
	   a multiple of 64 bytes.  */
	if (var->xres * (par->tga_type == TGA_TYPE_8PLANE ? 1 : 4) % 64)
		return -EINVAL;

	return 0;
}