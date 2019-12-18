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
 int /*<<< orphan*/  GP2X_BTN_PUSH ; 
 size_t GP2X_BTN_SELECT ; 
 size_t GP2X_BTN_VOL_DOWN ; 
 size_t GP2X_BTN_VOL_UP ; 
 int IN_BINDTYPE_COUNT ; 
 int IN_BINDTYPE_EMU ; 
 size_t IN_BIND_OFFS (size_t,int) ; 
 int IN_GP2X_NBUTTONS ; 
 int PEV_MENU ; 
 int PEV_VOL_DOWN ; 
 int PEV_VOL_UP ; 
 int eb ; 
 int have_menu ; 
 int have_vol ; 
 int /*<<< orphan*/  in_combos_find (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_gp2x_combo_acts ; 
 int /*<<< orphan*/  in_gp2x_combo_keys ; 
 int /*<<< orphan*/ ** in_gp2x_keys ; 

__attribute__((used)) static int in_gp2x_clean_binds(void *drv_data, int *binds, int *def_binds)
{
	int i, count = 0;
//	int eb, have_vol = 0, have_menu = 0;

	for (i = 0; i < IN_GP2X_NBUTTONS; i++) {
		int t, offs;
		for (t = 0; t < IN_BINDTYPE_COUNT; t++) {
			offs = IN_BIND_OFFS(i, t);
			if (in_gp2x_keys[i] == NULL)
				binds[offs] = def_binds[offs] = 0;
			if (binds[offs])
				count++;
		}
#if 0
		eb = binds[IN_BIND_OFFS(i, IN_BINDTYPE_EMU)];
		if (eb & (PEV_VOL_DOWN|PEV_VOL_UP))
			have_vol = 1;
		if (eb & PEV_MENU)
			have_menu = 1;
#endif
	}

	// TODO: move to pico
#if 0
	/* autobind some important keys, if they are unbound */
	if (!have_vol && binds[GP2X_BTN_VOL_UP] == 0 && binds[GP2X_BTN_VOL_DOWN] == 0) {
		binds[IN_BIND_OFFS(GP2X_BTN_VOL_UP, IN_BINDTYPE_EMU)]   = PEV_VOL_UP;
		binds[IN_BIND_OFFS(GP2X_BTN_VOL_DOWN, IN_BINDTYPE_EMU)] = PEV_VOL_DOWN;
		count += 2;
	}

	if (!have_menu) {
		binds[IN_BIND_OFFS(GP2X_BTN_SELECT, IN_BINDTYPE_EMU)] = PEV_MENU;
		count++;
	}
#endif

	in_combos_find(binds, GP2X_BTN_PUSH, &in_gp2x_combo_keys, &in_gp2x_combo_acts);

	return count;
}