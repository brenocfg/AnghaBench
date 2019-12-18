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
struct TYPE_3__ {int bits_per_pixel; int /*<<< orphan*/  accel_flags; } ;
struct fb_info {TYPE_2__ fix; scalar_t__ pseudo_palette; TYPE_1__ var; struct i810fb_par* par; } ;
struct fb_image {int depth; int fg_color; int bg_color; int dy; int dx; int width; int height; scalar_t__ data; } ;

/* Variables and functions */
 int LOCKUP ; 
 int /*<<< orphan*/  PAT_COPY_ROP ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  mono_src_copy_imm_blit (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,struct fb_info*) ; 

void i810fb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct i810fb_par *par = info->par;
	u32 fg = 0, bg = 0, size, dst;
	
	if (!info->var.accel_flags || par->dev_flags & LOCKUP ||
	    par->depth == 4 || image->depth != 1) {
		cfb_imageblit(info, image);
		return;
	}

	switch (info->var.bits_per_pixel) {
	case 8:
		fg = image->fg_color;
		bg = image->bg_color;
		break;
	case 16:
	case 24:
		fg = ((u32 *)(info->pseudo_palette))[image->fg_color];
		bg = ((u32 *)(info->pseudo_palette))[image->bg_color];
		break;
	}	
	
	dst = info->fix.smem_start + (image->dy * info->fix.line_length) + 
		(image->dx * par->depth);

	size = (image->width+7)/8 + 1;
	size &= ~1;
	size *= image->height;
	size += 7;
	size &= ~7;
	mono_src_copy_imm_blit(image->width * par->depth, 
			       image->height, info->fix.line_length, 
			       size/4, par->blit_bpp,
			       PAT_COPY_ROP, dst, (u32 *) image->data, 
			       bg, fg, info);
}