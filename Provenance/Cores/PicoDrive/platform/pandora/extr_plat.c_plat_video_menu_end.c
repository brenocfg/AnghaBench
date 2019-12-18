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
 int /*<<< orphan*/  g_menuscreen_ptr ; 
 int /*<<< orphan*/  main_fb ; 
 int /*<<< orphan*/  vout_fbdev_flip (int /*<<< orphan*/ ) ; 

void plat_video_menu_end(void)
{
	g_menuscreen_ptr = vout_fbdev_flip(main_fb);
}