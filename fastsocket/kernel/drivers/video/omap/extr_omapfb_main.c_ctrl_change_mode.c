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
struct TYPE_6__ {int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  channel_out; } ;
struct omapfb_plane_struct {TYPE_3__ info; int /*<<< orphan*/  idx; int /*<<< orphan*/  color_mode; struct omapfb_device* fbdev; } ;
struct omapfb_device {TYPE_2__* ctrl; } ;
struct fb_var_screeninfo {int yoffset; int xoffset; int bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  rotate; int /*<<< orphan*/  xres_virtual; } ;
struct TYPE_4__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; struct fb_var_screeninfo var; struct omapfb_plane_struct* par; } ;
struct TYPE_5__ {int (* setup_plane ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* set_rotate ) (int /*<<< orphan*/ ) ;int (* set_scale ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sync ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctrl_change_mode(struct fb_info *fbi)
{
	int r;
	unsigned long offset;
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	struct fb_var_screeninfo *var = &fbi->var;

	offset = var->yoffset * fbi->fix.line_length +
		 var->xoffset * var->bits_per_pixel / 8;

	if (fbdev->ctrl->sync)
		fbdev->ctrl->sync();
	r = fbdev->ctrl->setup_plane(plane->idx, plane->info.channel_out,
				 offset, var->xres_virtual,
				 plane->info.pos_x, plane->info.pos_y,
				 var->xres, var->yres, plane->color_mode);
	if (r < 0)
		return r;

	if (fbdev->ctrl->set_rotate != NULL) {
		r = fbdev->ctrl->set_rotate(var->rotate);
		if (r < 0)
			return r;
	}

	if (fbdev->ctrl->set_scale != NULL)
		r = fbdev->ctrl->set_scale(plane->idx,
				   var->xres, var->yres,
				   plane->info.out_width,
				   plane->info.out_height);

	return r;
}