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
#define  GP2X_DEV_CAANOO 130 
#define  GP2X_DEV_GP2X 129 
#define  GP2X_DEV_WIZ 128 
 int flip_after_sync ; 
 int /*<<< orphan*/  g_menubg_ptr ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 int gp2x_dev_id ; 
 int /*<<< orphan*/  gp2x_evdev_pdata ; 
 int /*<<< orphan*/  gp2x_make_fb_bufferable (int) ; 
 int /*<<< orphan*/  gp2x_memset_all_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gp2x_menu_init () ; 
 int /*<<< orphan*/ * gp2x_screens ; 
 int /*<<< orphan*/  in_evdev_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_gp2x_defbinds ; 
 int /*<<< orphan*/  in_gp2x_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_probe () ; 
 int /*<<< orphan*/  plat_target_setup_input () ; 
 int /*<<< orphan*/  sharedmem940_init () ; 
 int /*<<< orphan*/  vid_mmsp2_init () ; 
 int /*<<< orphan*/  vid_pollux_init () ; 
 int /*<<< orphan*/  warm_init () ; 

void plat_init(void)
{
	warm_init();

	switch (gp2x_dev_id) {
	case GP2X_DEV_GP2X:
		sharedmem940_init();
		vid_mmsp2_init();
		break;
	case GP2X_DEV_WIZ:
	case GP2X_DEV_CAANOO:
		vid_pollux_init();
		break;
	}

	g_menuscreen_w = 320;
	g_menuscreen_h = 240;
	gp2x_memset_all_buffers(0, 0, 320*240*2);

	gp2x_make_fb_bufferable(1);

	// use buffer2 for menubg to save mem (using only buffers 0, 1 in menu)
	g_menubg_ptr = gp2x_screens[2];

	flip_after_sync = 1;
	gp2x_menu_init();

	in_evdev_init(&gp2x_evdev_pdata);
	in_gp2x_init(in_gp2x_defbinds);
	in_probe();
	plat_target_setup_input();
}