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
 scalar_t__ g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int me_sfont_h ; 
 int /*<<< orphan*/  memset (unsigned short*,int,int) ; 
 int /*<<< orphan*/  menu_draw_begin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 

__attribute__((used)) static void load_progress_cb(int percent)
{
	int ln, len = percent * g_menuscreen_w / 100;
	unsigned short *dst;

	if (len > g_menuscreen_w)
		len = g_menuscreen_w;

	menu_draw_begin(0, 1);
	dst = (unsigned short *)g_menuscreen_ptr + g_menuscreen_w * me_sfont_h * 2;
	for (ln = me_sfont_h - 2; ln > 0; ln--, dst += g_menuscreen_w)
		memset(dst, 0xff, len * 2);
	menu_draw_end();
}