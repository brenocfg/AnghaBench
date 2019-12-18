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
 int g_menuscreen_h ; 
 int /*<<< orphan*/  g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int /*<<< orphan*/  main_fb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vout_fbdev_flip (int /*<<< orphan*/ ) ; 

void plat_video_loop_prepare(void)
{
	// make sure there is no junk left behind the layer
	memset(g_menuscreen_ptr, 0, g_menuscreen_w * g_menuscreen_h * 2);
	g_menuscreen_ptr = vout_fbdev_flip(main_fb);

	// emu_video_mode_change will call pnd_setup_layer()
}