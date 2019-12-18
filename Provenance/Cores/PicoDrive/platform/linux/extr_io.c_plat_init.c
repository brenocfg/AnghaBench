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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  g_menubg_ptr ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 int g_screen_height ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc_screen () ; 
 int vout_fbdev_init (int*,int*) ; 
 int /*<<< orphan*/  xlib_init () ; 

void plat_init(void)
{
#ifdef FBDEV
	int ret, w, h;
	ret = vout_fbdev_init(&w, &h);
	if (ret != 0)
		exit(1);
	g_screen_width = g_menuscreen_w = w;
	g_screen_height = g_menuscreen_h = h;
	g_menubg_ptr = realloc(g_menubg_ptr, w * g_screen_height * 2);
#else
	realloc_screen();
	memset(g_screen_ptr, 0, g_screen_width * g_screen_height * 2);
	xlib_init();
#endif
}