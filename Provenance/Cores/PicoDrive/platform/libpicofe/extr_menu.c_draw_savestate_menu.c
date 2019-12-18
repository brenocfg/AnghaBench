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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  time_buf ;
struct tm {int dummy; } ;

/* Variables and functions */
 int STATE_SLOT_COUNT ; 
 int /*<<< orphan*/  draw_savestate_bg (int) ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 struct tm* localtime (scalar_t__*) ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 int /*<<< orphan*/  menu_draw_begin (int,int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 int state_slot_flags ; 
 scalar_t__* state_slot_times ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  text_out16 (int,int,char*,...) ; 

__attribute__((used)) static void draw_savestate_menu(int menu_sel, int is_loading)
{
	int i, x, y, w, h;
	char time_buf[32];

	if (state_slot_flags & (1 << menu_sel))
		draw_savestate_bg(menu_sel);

	w = (13 + 2) * me_mfont_w;
	h = (1+2+STATE_SLOT_COUNT+1) * me_mfont_h;
	x = g_menuscreen_w / 2 - w / 2;
	if (x < 0) x = 0;
	y = g_menuscreen_h / 2 - h / 2;
	if (y < 0) y = 0;
#ifdef MENU_ALIGN_LEFT
	if (x > 12 + me_mfont_w * 2)
		x = 12 + me_mfont_w * 2;
#endif

	menu_draw_begin(1, 1);

	text_out16(x, y, is_loading ? "Load state" : "Save state");
	y += 3 * me_mfont_h;

	menu_draw_selection(x - me_mfont_w * 2, y + menu_sel * me_mfont_h, (23 + 2) * me_mfont_w + 4);

	/* draw all slots */
	for (i = 0; i < STATE_SLOT_COUNT; i++, y += me_mfont_h)
	{
		if (!(state_slot_flags & (1 << i)))
			strcpy(time_buf, "free");
		else {
			strcpy(time_buf, "USED");
			if (state_slot_times[i] != 0) {
				time_t time = state_slot_times[i];
				struct tm *t = localtime(&time);
				strftime(time_buf, sizeof(time_buf), "%x %R", t);
			}
		}

		text_out16(x, y, "SLOT %i (%s)", i, time_buf);
	}
	text_out16(x, y, "back");

	menu_draw_end();
}