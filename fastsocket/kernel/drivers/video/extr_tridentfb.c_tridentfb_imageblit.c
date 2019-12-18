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
struct tridentfb_par {int /*<<< orphan*/  (* image_blit ) (struct tridentfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* wait_engine ) (struct tridentfb_par*) ;} ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {int flags; scalar_t__ pseudo_palette; TYPE_1__ var; struct tridentfb_par* par; } ;
struct fb_image {int depth; int fg_color; int bg_color; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  stub1 (struct tridentfb_par*) ; 
 int /*<<< orphan*/  stub2 (struct tridentfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void tridentfb_imageblit(struct fb_info *info,
				const struct fb_image *img)
{
	struct tridentfb_par *par = info->par;
	int col, bgcol;

	if ((info->flags & FBINFO_HWACCEL_DISABLED) || img->depth != 1) {
		cfb_imageblit(info, img);
		return;
	}
	if (info->var.bits_per_pixel == 8) {
		col = img->fg_color;
		col |= col << 8;
		col |= col << 16;
		bgcol = img->bg_color;
		bgcol |= bgcol << 8;
		bgcol |= bgcol << 16;
	} else {
		col = ((u32 *)(info->pseudo_palette))[img->fg_color];
		bgcol = ((u32 *)(info->pseudo_palette))[img->bg_color];
	}

	par->wait_engine(par);
	if (par->image_blit)
		par->image_blit(par, img->data, img->dx, img->dy,
				img->width, img->height, col, bgcol);
	else
		cfb_imageblit(info, img);
}