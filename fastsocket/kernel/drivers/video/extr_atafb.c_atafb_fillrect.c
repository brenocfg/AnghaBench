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
struct fb_fillrect {int width; int height; int dx; int dy; int /*<<< orphan*/  color; } ;
struct atafb_par {int /*<<< orphan*/  next_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  atafb_iplan2p2_fillrect (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  atafb_iplan2p4_fillrect (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  atafb_iplan2p8_fillrect (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  atafb_mfb_fillrect (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void atafb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct atafb_par *par = (struct atafb_par *)info->par;
	int x2, y2;
	u32 width, height;

	if (!rect->width || !rect->height)
		return;

#ifdef ATAFB_FALCON
	if (info->var.bits_per_pixel == 16) {
		cfb_fillrect(info, rect);
		return;
	}
#endif

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly.
	 * */
	x2 = rect->dx + rect->width;
	y2 = rect->dy + rect->height;
	x2 = x2 < info->var.xres_virtual ? x2 : info->var.xres_virtual;
	y2 = y2 < info->var.yres_virtual ? y2 : info->var.yres_virtual;
	width = x2 - rect->dx;
	height = y2 - rect->dy;

	if (info->var.bits_per_pixel == 1)
		atafb_mfb_fillrect(info, par->next_line, rect->color,
				   rect->dy, rect->dx, height, width);
	else if (info->var.bits_per_pixel == 2)
		atafb_iplan2p2_fillrect(info, par->next_line, rect->color,
					rect->dy, rect->dx, height, width);
	else if (info->var.bits_per_pixel == 4)
		atafb_iplan2p4_fillrect(info, par->next_line, rect->color,
					rect->dy, rect->dx, height, width);
	else
		atafb_iplan2p8_fillrect(info, par->next_line, rect->color,
					rect->dy, rect->dx, height, width);

	return;
}