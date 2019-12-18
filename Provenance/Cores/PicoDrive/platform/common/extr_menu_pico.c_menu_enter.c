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
 int /*<<< orphan*/  READPNG_BG ; 
 int /*<<< orphan*/  g_menubg_ptr ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 int /*<<< orphan*/  make_bg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int plat_get_skin_dir (char*,int) ; 
 int /*<<< orphan*/  plat_video_menu_enter (int) ; 
 scalar_t__ readpng (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void menu_enter(int is_rom_loaded)
{
	if (is_rom_loaded)
	{
		make_bg(0);
	}
	else
	{
		int pos;
		char buff[256];
		pos = plat_get_skin_dir(buff, 256);
		strcpy(buff + pos, "background.png");

		// should really only happen once, on startup..
		if (readpng(g_menubg_ptr, buff, READPNG_BG,
						g_menuscreen_w, g_menuscreen_h) < 0)
			memset(g_menubg_ptr, 0, g_menuscreen_w * g_menuscreen_h * 2);
	}

	plat_video_menu_enter(is_rom_loaded);
}