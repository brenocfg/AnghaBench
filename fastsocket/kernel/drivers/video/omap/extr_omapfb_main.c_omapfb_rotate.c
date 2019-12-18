#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omapfb_plane_struct {struct omapfb_device* fbdev; } ;
struct fb_var_screeninfo {int rotate; } ;
struct omapfb_device {struct fb_var_screeninfo new_var; } ;
struct fb_info {struct fb_var_screeninfo var; struct omapfb_plane_struct* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_change_mode (struct fb_info*) ; 
 scalar_t__ memcmp (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 scalar_t__ set_fb_var (struct fb_info*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static void omapfb_rotate(struct fb_info *fbi, int rotate)
{
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;

	omapfb_rqueue_lock(fbdev);
	if (rotate != fbi->var.rotate) {
		struct fb_var_screeninfo *new_var = &fbdev->new_var;

		memcpy(new_var, &fbi->var, sizeof(*new_var));
		new_var->rotate = rotate;
		if (set_fb_var(fbi, new_var) == 0 &&
		    memcmp(new_var, &fbi->var, sizeof(*new_var))) {
			memcpy(&fbi->var, new_var, sizeof(*new_var));
			ctrl_change_mode(fbi);
		}
	}
	omapfb_rqueue_unlock(fbdev);
}