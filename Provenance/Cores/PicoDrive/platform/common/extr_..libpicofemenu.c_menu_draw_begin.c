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
 int borders_pending ; 
 scalar_t__ g_border_style ; 
 int /*<<< orphan*/  g_menubg_ptr ; 
 int g_menuscreen_h ; 
 int /*<<< orphan*/  g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_darken_bg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  menu_reset_borders () ; 
 int /*<<< orphan*/  plat_video_menu_begin () ; 

__attribute__((used)) static void menu_draw_begin(int need_bg, int no_borders)
{
	plat_video_menu_begin();

	menu_reset_borders();
	borders_pending = g_border_style && !no_borders;

	if (need_bg) {
		if (g_border_style && no_borders) {
			menu_darken_bg(g_menuscreen_ptr, g_menubg_ptr,
				g_menuscreen_w * g_menuscreen_h, 1);
		}
		else {
			memcpy(g_menuscreen_ptr, g_menubg_ptr,
				g_menuscreen_w * g_menuscreen_h * 2);
		}
	}
}