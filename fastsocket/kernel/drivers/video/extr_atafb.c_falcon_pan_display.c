#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_7__ {int bits_per_pixel; int xres_virtual; int xres; } ;
struct fb_info {TYPE_3__ var; scalar_t__ par; } ;
struct TYPE_5__ {int xoffset; int line_offset; } ;
struct TYPE_6__ {TYPE_1__ falcon; } ;
struct atafb_par {scalar_t__ screen_base; TYPE_2__ hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_screen_base ) (scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int f_pan_display ; 
 TYPE_4__* fbhw ; 
 scalar_t__ screen_base ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 void* up (int,int) ; 

__attribute__((used)) static int falcon_pan_display(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct atafb_par *par = (struct atafb_par *)info->par;

	int xoffset;
	int bpp = info->var.bits_per_pixel;

	if (bpp == 1)
		var->xoffset = up(var->xoffset, 32);
	if (bpp != 16)
		par->hw.falcon.xoffset = var->xoffset & 15;
	else {
		par->hw.falcon.xoffset = 0;
		var->xoffset = up(var->xoffset, 2);
	}
	par->hw.falcon.line_offset = bpp *
		(info->var.xres_virtual - info->var.xres) / 16;
	if (par->hw.falcon.xoffset)
		par->hw.falcon.line_offset -= bpp;
	xoffset = var->xoffset - par->hw.falcon.xoffset;

	par->screen_base = screen_base +
	        (var->yoffset * info->var.xres_virtual + xoffset) * bpp / 8;
	if (fbhw->set_screen_base)
		fbhw->set_screen_base(par->screen_base);
	else
		return -EINVAL;		/* shouldn't happen */
	f_pan_display = 1;
	return 0;
}