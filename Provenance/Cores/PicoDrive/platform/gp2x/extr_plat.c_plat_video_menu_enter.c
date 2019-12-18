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

/* Variables and functions */
 scalar_t__ GP2X_DEV_WIZ ; 
 int gp2x_current_bpp ; 
 scalar_t__ gp2x_dev_id ; 
 int /*<<< orphan*/ * gp2x_screens ; 
 int /*<<< orphan*/  gp2x_video_RGB_setscaling (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gp2x_video_changemode_ll (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp2x_video_flip2 () ; 
 int /*<<< orphan*/  gp2x_video_wait_vsync () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void plat_video_menu_enter(int is_rom_loaded)
{
	if (gp2x_current_bpp != 16 || gp2x_dev_id == GP2X_DEV_WIZ) {
		/* try to switch nicely avoiding glitches */
		gp2x_video_wait_vsync();
		memset(gp2x_screens[0], 0, 320*240*2);
		memset(gp2x_screens[1], 0, 320*240*2);
		gp2x_video_flip2(); // might flip to fb2/3
		gp2x_video_flip2(); // ..so we do it again
	}
	else
		gp2x_video_flip2();

	// switch to 16bpp
	gp2x_video_changemode_ll(16, 0);
	gp2x_video_RGB_setscaling(0, 320, 240);
}