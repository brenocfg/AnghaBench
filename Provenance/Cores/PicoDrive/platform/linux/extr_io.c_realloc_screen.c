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
 int /*<<< orphan*/  g_menubg_ptr ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 int g_screen_height ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ scr_changed ; 
 int scr_h ; 
 int scr_w ; 

__attribute__((used)) static void realloc_screen(void)
{
	int size = scr_w * scr_h * 2;
	g_screen_width = g_menuscreen_w = scr_w;
	g_screen_height = g_menuscreen_h = scr_h;
	g_screen_ptr = realloc(g_screen_ptr, size);
	g_menubg_ptr = realloc(g_menubg_ptr, size);
	memset(g_screen_ptr, 0, size);
	memset(g_menubg_ptr, 0, size);
	scr_changed = 0;
}