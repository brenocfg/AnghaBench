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
struct tridentfb_par {int /*<<< orphan*/  (* fill_rect ) (struct tridentfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* wait_engine ) (struct tridentfb_par*) ;} ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {int flags; scalar_t__ pseudo_palette; TYPE_1__ var; struct tridentfb_par* par; } ;
struct fb_fillrect {int color; int /*<<< orphan*/  rop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  stub1 (struct tridentfb_par*) ; 
 int /*<<< orphan*/  stub2 (struct tridentfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tridentfb_fillrect(struct fb_info *info,
			       const struct fb_fillrect *fr)
{
	struct tridentfb_par *par = info->par;
	int col;

	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_fillrect(info, fr);
		return;
	}
	if (info->var.bits_per_pixel == 8) {
		col = fr->color;
		col |= col << 8;
		col |= col << 16;
	} else
		col = ((u32 *)(info->pseudo_palette))[fr->color];

	par->wait_engine(par);
	par->fill_rect(par, fr->dx, fr->dy, fr->width,
		       fr->height, col, fr->rop);
}