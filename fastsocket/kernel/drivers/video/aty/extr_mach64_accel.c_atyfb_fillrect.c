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
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; scalar_t__ par; } ;
struct fb_fillrect {int color; int dx; int width; int /*<<< orphan*/  height; int /*<<< orphan*/  dy; } ;
struct atyfb_par {int /*<<< orphan*/  accel_flags; scalar_t__ asleep; } ;

/* Variables and functions */
 int BKGD_SRC_BKGD_CLR ; 
 int /*<<< orphan*/  DP_FRGD_CLR ; 
 int /*<<< orphan*/  DP_SRC ; 
 int /*<<< orphan*/  DST_CNTL ; 
 int DST_LAST_PEL ; 
 int DST_X_LEFT_TO_RIGHT ; 
 int DST_Y_TOP_TO_BOTTOM ; 
 int FRGD_SRC_FRGD_CLR ; 
 int MONO_SRC_ONE ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  draw_rect (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int rotation24bpp (int,int) ; 
 int /*<<< orphan*/  wait_for_fifo (int,struct atyfb_par*) ; 

void atyfb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 color = rect->color, dx = rect->dx, width = rect->width, rotation = 0;

	if (par->asleep)
		return;
	if (!rect->width || !rect->height)
		return;
	if (!par->accel_flags) {
		cfb_fillrect(info, rect);
		return;
	}

	color |= (rect->color << 8);
	color |= (rect->color << 16);

	if (info->var.bits_per_pixel == 24) {
		/* In 24 bpp, the engine is in 8 bpp - this requires that all */
		/* horizontal coordinates and widths must be adjusted */
		dx *= 3;
		width *= 3;
		rotation = rotation24bpp(dx, DST_X_LEFT_TO_RIGHT);
	}

	wait_for_fifo(3, par);
	aty_st_le32(DP_FRGD_CLR, color, par);
	aty_st_le32(DP_SRC,
		    BKGD_SRC_BKGD_CLR | FRGD_SRC_FRGD_CLR | MONO_SRC_ONE,
		    par);
	aty_st_le32(DST_CNTL,
		    DST_LAST_PEL | DST_Y_TOP_TO_BOTTOM |
		    DST_X_LEFT_TO_RIGHT | rotation, par);
	draw_rect(dx, rect->dy, width, rect->height, par);
}