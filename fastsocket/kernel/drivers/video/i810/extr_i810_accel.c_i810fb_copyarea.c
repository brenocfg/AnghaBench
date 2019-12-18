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
struct TYPE_4__ {int line_length; int smem_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  accel_flags; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct i810fb_par* par; } ;
struct fb_copyarea {int dx; int sx; int width; int sy; int dy; int height; } ;

/* Variables and functions */
 int DECREMENT ; 
 int INCREMENT ; 
 int LOCKUP ; 
 int /*<<< orphan*/  PAT_COPY_ROP ; 
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  source_copy_blit (int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fb_info*) ; 

void i810fb_copyarea(struct fb_info *info, const struct fb_copyarea *region) 
{
	struct i810fb_par *par = info->par;
	u32 sx, sy, dx, dy, pitch, width, height, src, dest, xdir;

	if (!info->var.accel_flags || par->dev_flags & LOCKUP ||
	    par->depth == 4) {
		cfb_copyarea(info, region);
		return;
	}

	dx = region->dx * par->depth;
	sx = region->sx * par->depth;
	width = region->width * par->depth;
	sy = region->sy;
	dy = region->dy;
	height = region->height;

	if (dx <= sx) {
		xdir = INCREMENT;
	}
	else {
		xdir = DECREMENT;
		sx += width - 1;
		dx += width - 1;
	}
	if (dy <= sy) {
		pitch = info->fix.line_length;
	}
	else {
		pitch = (-(info->fix.line_length)) & 0xFFFF;
		sy += height - 1;
		dy += height - 1;
	}
	src = info->fix.smem_start + (sy * info->fix.line_length) + sx;
	dest = info->fix.smem_start + (dy * info->fix.line_length) + dx;

	source_copy_blit(width, height, pitch, xdir, src, dest,
			 PAT_COPY_ROP, par->blit_bpp, info);
}