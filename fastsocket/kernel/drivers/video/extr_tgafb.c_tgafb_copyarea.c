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
struct TYPE_4__ {unsigned long xres_virtual; unsigned long yres_virtual; unsigned long bits_per_pixel; } ;
struct TYPE_3__ {unsigned long line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; } ;
struct fb_copyarea {unsigned long dx; unsigned long dy; unsigned long width; unsigned long height; unsigned long sx; unsigned long sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  copyarea_backward_8bpp (struct fb_info*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  copyarea_foreward_8bpp (struct fb_info*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  copyarea_line_32bpp (struct fb_info*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  copyarea_line_8bpp (struct fb_info*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void
tgafb_copyarea(struct fb_info *info, const struct fb_copyarea *area) 
{
	unsigned long dx, dy, width, height, sx, sy, vxres, vyres;
	unsigned long line_length, bpp;

	dx = area->dx;
	dy = area->dy;
	width = area->width;
	height = area->height;
	sx = area->sx;
	sy = area->sy;
	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;
	line_length = info->fix.line_length;

	/* The top left corners must be in the virtual screen.  */
	if (dx > vxres || sx > vxres || dy > vyres || sy > vyres)
		return;

	/* Clip the destination.  */
	if (dx + width > vxres)
		width = vxres - dx;
	if (dy + height > vyres)
		height = vyres - dy;

	/* The source must be completely inside the virtual screen.  */
	if (sx + width > vxres || sy + height > vyres)
		return;

	bpp = info->var.bits_per_pixel;

	/* Detect copies of the entire line.  */
	if (width * (bpp >> 3) == line_length) {
		if (bpp == 8)
			copyarea_line_8bpp(info, dy, sy, height, width);
		else
			copyarea_line_32bpp(info, dy, sy, height, width);
	}

	/* ??? The documentation is unclear to me exactly how the pixelshift
	   register works in 32bpp mode.  Since I don't have hardware to test,
	   give up for now and fall back on the generic routines.  */
	else if (bpp == 32)
		cfb_copyarea(info, area);

	/* Detect overlapping source and destination that requires
	   a backward copy.  */
	else if (dy == sy && dx > sx && dx < sx + width)
		copyarea_backward_8bpp(info, dx, dy, sx, sy, height,
				       width, line_length, area);
	else
		copyarea_foreward_8bpp(info, dx, dy, sx, sy, height,
				       width, line_length);
}