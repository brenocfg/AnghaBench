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
 unsigned long PBTN_CIRCLE ; 
 unsigned long PBTN_DOWN ; 
 unsigned long PBTN_UP ; 
 unsigned long PBTN_X ; 
 int /*<<< orphan*/  PicoStateProgressCB ; 
 int /*<<< orphan*/  draw_savestate_menu (int,int) ; 
 scalar_t__ emu_SaveLoadGame (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_msg_cb ; 
 unsigned long in_menu_wait (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menuErrorMsg ; 
 int /*<<< orphan*/  state_check_slots () ; 
 int state_slot ; 
 int state_slot_flags ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int savestate_menu_loop(int is_loading)
{
	static int menu_sel = 10;
	int menu_sel_max = 10;
	unsigned long inp = 0;

	state_check_slots();

	for(;;)
	{
		draw_savestate_menu(menu_sel, is_loading);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_X|PBTN_CIRCLE, 0);
		if(inp & PBTN_UP  ) {
			do {
				menu_sel--; if (menu_sel < 0) menu_sel = menu_sel_max;
			} while (!(state_slot_flags & (1 << menu_sel)) && menu_sel != menu_sel_max && is_loading);
		}
		if(inp & PBTN_DOWN) {
			do {
				menu_sel++; if (menu_sel > menu_sel_max) menu_sel = 0;
			} while (!(state_slot_flags & (1 << menu_sel)) && menu_sel != menu_sel_max && is_loading);
		}
		if(inp & PBTN_CIRCLE) { // save/load
			if (menu_sel < 10) {
				state_slot = menu_sel;
				PicoStateProgressCB = emu_msg_cb; /* also suitable for menu */
				if (emu_SaveLoadGame(is_loading, 0)) {
					strcpy(menuErrorMsg, is_loading ? "Load failed" : "Save failed");
					return 1;
				}
				return 0;
			} else	return 1;
		}
		if(inp & PBTN_X) return 1;
	}
}