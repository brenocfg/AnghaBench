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
struct omapfb_device {int dummy; } ;
struct fb_info {struct omapfb_plane_struct* par; } ;

/* Variables and functions */
 int ctrl_change_mode (struct fb_info*) ; 
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 int /*<<< orphan*/  set_fb_fix (struct fb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapfb_set_par(struct fb_info *fbi)
{
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	int r = 0;

	omapfb_rqueue_lock(fbdev);
	set_fb_fix(fbi, 0);
	r = ctrl_change_mode(fbi);
	omapfb_rqueue_unlock(fbdev);

	return r;
}