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
typedef  int /*<<< orphan*/  win ;
typedef  int /*<<< orphan*/  u16 ;
struct omapfb_update_window {int width; int height; int out_width; int out_height; } ;
struct TYPE_4__ {TYPE_3__* region; } ;
struct omapfb_device {int /*<<< orphan*/ * fb_info; TYPE_2__* ctrl; TYPE_1__ mem_desc; } ;
struct TYPE_6__ {scalar_t__ vaddr; } ;
struct TYPE_5__ {scalar_t__ (* get_update_mode ) () ;int /*<<< orphan*/  (* update_window ) (int /*<<< orphan*/ ,struct omapfb_update_window*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ OMAPFB_MANUAL_UPDATE ; 
 int /*<<< orphan*/  memset (struct omapfb_update_window*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct omapfb_update_window*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void omapfb_write_first_pixel(struct omapfb_device *fbdev, u16 pixval)
{
	omapfb_rqueue_lock(fbdev);
	*(u16 *)fbdev->mem_desc.region[0].vaddr = pixval;
	if (fbdev->ctrl->get_update_mode() == OMAPFB_MANUAL_UPDATE) {
		struct omapfb_update_window win;

		memset(&win, 0, sizeof(win));
		win.width = 2;
		win.height = 2;
		win.out_width = 2;
		win.out_height = 2;
		fbdev->ctrl->update_window(fbdev->fb_info[0], &win, NULL, NULL);
	}
	omapfb_rqueue_unlock(fbdev);
}