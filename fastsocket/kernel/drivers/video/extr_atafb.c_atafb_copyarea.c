#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int bits_per_pixel; int xres_virtual; int yres_virtual; } ;
struct fb_info {TYPE_1__ var; scalar_t__ par; } ;
struct fb_copyarea {int dx; int width; int dy; int height; int sx; int sy; } ;
struct atafb_par {int /*<<< orphan*/  next_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  atafb_iplan2p2_copyarea (struct fb_info*,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  atafb_iplan2p4_copyarea (struct fb_info*,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  atafb_iplan2p8_copyarea (struct fb_info*,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  atafb_mfb_copyarea (struct fb_info*,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 

__attribute__((used)) static void atafb_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{
	struct atafb_par *par = (struct atafb_par *)info->par;
	int x2, y2;
	u32 dx, dy, sx, sy, width, height;
	int rev_copy = 0;

#ifdef ATAFB_FALCON
	if (info->var.bits_per_pixel == 16) {
		cfb_copyarea(info, area);
		return;
	}
#endif

	/* clip the destination */
	x2 = area->dx + area->width;
	y2 = area->dy + area->height;
	dx = area->dx > 0 ? area->dx : 0;
	dy = area->dy > 0 ? area->dy : 0;
	x2 = x2 < info->var.xres_virtual ? x2 : info->var.xres_virtual;
	y2 = y2 < info->var.yres_virtual ? y2 : info->var.yres_virtual;
	width = x2 - dx;
	height = y2 - dy;

	if (area->sx + dx < area->dx || area->sy + dy < area->dy)
		return;

	/* update sx,sy */
	sx = area->sx + (dx - area->dx);
	sy = area->sy + (dy - area->dy);

	/* the source must be completely inside the virtual screen */
	if (sx + width > info->var.xres_virtual ||
			sy + height > info->var.yres_virtual)
		return;

	if (dy > sy || (dy == sy && dx > sx)) {
		dy += height;
		sy += height;
		rev_copy = 1;
	}

	if (info->var.bits_per_pixel == 1)
		atafb_mfb_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);
	else if (info->var.bits_per_pixel == 2)
		atafb_iplan2p2_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);
	else if (info->var.bits_per_pixel == 4)
		atafb_iplan2p4_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);
	else
		atafb_iplan2p8_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);

	return;
}