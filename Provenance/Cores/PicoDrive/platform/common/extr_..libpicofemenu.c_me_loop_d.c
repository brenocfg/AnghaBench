#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* handler ) (int /*<<< orphan*/ ,int) ;scalar_t__ beh; int /*<<< orphan*/  id; int /*<<< orphan*/  selectable; int /*<<< orphan*/  enabled; } ;
typedef  TYPE_1__ menu_entry ;

/* Variables and functions */
 scalar_t__ MB_NONE ; 
 int PBTN_DOWN ; 
 int PBTN_L ; 
 int PBTN_LEFT ; 
 int PBTN_MBACK ; 
 int PBTN_MENU ; 
 int PBTN_MOK ; 
 int PBTN_R ; 
 int PBTN_RIGHT ; 
 int PBTN_UP ; 
 int /*<<< orphan*/  debug_menu_loop () ; 
 int in_menu_wait (int,int /*<<< orphan*/ *,int) ; 
 int in_menu_wait_any (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int me_count (TYPE_1__*) ; 
 int /*<<< orphan*/  me_draw (TYPE_1__*,int,void (*) ()) ; 
 scalar_t__ me_process (TYPE_1__*,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int me_loop_d(menu_entry *menu, int *menu_sel, void (*draw_prep)(void), void (*draw_more)(void))
{
	int ret = 0, inp, sel = *menu_sel, menu_sel_max;

	menu_sel_max = me_count(menu) - 1;
	if (menu_sel_max < 0) {
		lprintf("no enabled menu entries\n");
		return 0;
	}

	while ((!menu[sel].enabled || !menu[sel].selectable) && sel < menu_sel_max)
		sel++;

	/* make sure action buttons are not pressed on entering menu */
	me_draw(menu, sel, NULL);
	while (in_menu_wait_any(NULL, 50) & (PBTN_MOK|PBTN_MBACK|PBTN_MENU));

	for (;;)
	{
		if (draw_prep != NULL)
			draw_prep();

		me_draw(menu, sel, draw_more);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT|
			PBTN_MOK|PBTN_MBACK|PBTN_MENU|PBTN_L|PBTN_R, NULL, 70);
		if (inp & (PBTN_MENU|PBTN_MBACK))
			break;

		if (inp & PBTN_UP  ) {
			do {
				sel--;
				if (sel < 0)
					sel = menu_sel_max;
			}
			while (!menu[sel].enabled || !menu[sel].selectable);
		}
		if (inp & PBTN_DOWN) {
			do {
				sel++;
				if (sel > menu_sel_max)
					sel = 0;
			}
			while (!menu[sel].enabled || !menu[sel].selectable);
		}

		/* a bit hacky but oh well */
		if ((inp & (PBTN_L|PBTN_R)) == (PBTN_L|PBTN_R))
			debug_menu_loop();

		if (inp & (PBTN_LEFT|PBTN_RIGHT|PBTN_L|PBTN_R)) { /* multi choice */
			if (me_process(&menu[sel], (inp & (PBTN_RIGHT|PBTN_R)) ? 1 : 0,
						inp & (PBTN_L|PBTN_R)))
				continue;
		}

		if (inp & (PBTN_MOK|PBTN_LEFT|PBTN_RIGHT|PBTN_L|PBTN_R))
		{
			/* require PBTN_MOK for MB_NONE */
			if (menu[sel].handler != NULL && (menu[sel].beh != MB_NONE || (inp & PBTN_MOK))) {
				ret = menu[sel].handler(menu[sel].id, inp);
				if (ret) break;
				menu_sel_max = me_count(menu) - 1; /* might change, so update */
			}
		}
	}
	*menu_sel = sel;

	return ret;
}