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
struct TYPE_4__ {unsigned int width; unsigned int height; } ;
struct vc_data {unsigned int vc_cols; unsigned int vc_rows; TYPE_1__ vc_font; scalar_t__ vc_hi_font_mask; } ;
struct TYPE_5__ {unsigned int xres; unsigned int yres; unsigned int yres_virtual; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct fb_info {TYPE_3__* fbops; TYPE_2__ var; } ;
struct fb_fillrect {unsigned int width; unsigned int height; scalar_t__ dy; scalar_t__ dx; int /*<<< orphan*/  rop; int /*<<< orphan*/  color; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fb_fillrect ) (struct fb_info*,struct fb_fillrect*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  attr_bgcol_ec (int,struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_fillrect*) ; 
 int /*<<< orphan*/  stub2 (struct fb_info*,struct fb_fillrect*) ; 

__attribute__((used)) static void bit_clear_margins(struct vc_data *vc, struct fb_info *info,
			      int bottom_only)
{
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	unsigned int cw = vc->vc_font.width;
	unsigned int ch = vc->vc_font.height;
	unsigned int rw = info->var.xres - (vc->vc_cols*cw);
	unsigned int bh = info->var.yres - (vc->vc_rows*ch);
	unsigned int rs = info->var.xres - rw;
	unsigned int bs = info->var.yres - bh;
	struct fb_fillrect region;

	region.color = attr_bgcol_ec(bgshift, vc, info);
	region.rop = ROP_COPY;

	if (rw && !bottom_only) {
		region.dx = info->var.xoffset + rs;
		region.dy = 0;
		region.width = rw;
		region.height = info->var.yres_virtual;
		info->fbops->fb_fillrect(info, &region);
	}

	if (bh) {
		region.dx = info->var.xoffset;
		region.dy = info->var.yoffset + bs;
		region.width = rs;
		region.height = bh;
		info->fbops->fb_fillrect(info, &region);
	}
}