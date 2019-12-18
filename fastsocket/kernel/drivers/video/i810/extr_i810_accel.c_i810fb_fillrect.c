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
typedef  int u32 ;
struct i810fb_par {int dev_flags; int depth; int /*<<< orphan*/  blit_bpp; } ;
struct TYPE_4__ {int smem_start; int line_length; } ;
struct TYPE_3__ {int /*<<< orphan*/  accel_flags; } ;
struct fb_info {TYPE_2__ fix; scalar_t__ pseudo_palette; TYPE_1__ var; struct i810fb_par* par; } ;
struct fb_fillrect {int color; size_t rop; int dx; int width; int dy; int height; } ;

/* Variables and functions */
 int LOCKUP ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  color_blit (int,int,int,int,int,int,int /*<<< orphan*/ ,struct fb_info*) ; 
 int* i810fb_rop ; 

void i810fb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct i810fb_par *par = info->par;
	u32 dx, dy, width, height, dest, rop = 0, color = 0;

	if (!info->var.accel_flags || par->dev_flags & LOCKUP ||
	    par->depth == 4) {
		cfb_fillrect(info, rect);
		return;
	}

	if (par->depth == 1) 
		color = rect->color;
	else 
		color = ((u32 *) (info->pseudo_palette))[rect->color];

	rop = i810fb_rop[rect->rop];

	dx = rect->dx * par->depth;
	width = rect->width * par->depth;
	dy = rect->dy;
	height = rect->height;

	dest = info->fix.smem_start + (dy * info->fix.line_length) + dx;
	color_blit(width, height, info->fix.line_length, dest, rop, color, 
		   par->blit_bpp, info);
}