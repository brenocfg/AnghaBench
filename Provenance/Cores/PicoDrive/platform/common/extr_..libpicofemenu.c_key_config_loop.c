#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mask; } ;
typedef  TYPE_1__ me_bind_action ;

/* Variables and functions */
 int IN_BINDTYPE_EMU ; 
 int IN_BINDTYPE_PLAYER12 ; 
 int /*<<< orphan*/  IN_CFG_DOES_COMBOS ; 
 int IN_MAX_DEVS ; 
#define  PBTN_DOWN 134 
#define  PBTN_LEFT 133 
#define  PBTN_MA2 132 
#define  PBTN_MBACK 131 
#define  PBTN_MOK 130 
#define  PBTN_RIGHT 129 
#define  PBTN_UP 128 
 int count_bound_keys (int,int,int) ; 
 int /*<<< orphan*/  draw_key_config (TYPE_1__ const*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  in_bind_key (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_get_config (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * in_get_dev_name (int,int,int /*<<< orphan*/ ) ; 
 int in_menu_wait (int,int /*<<< orphan*/ *,int) ; 
 int const in_menu_wait_any (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_unbind_all (int,int,int) ; 
 int in_update_keycode (int*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lprintf (char*) ; 

__attribute__((used)) static void key_config_loop(const me_bind_action *opts, int opt_cnt, int player_idx)
{
	int i, sel = 0, menu_sel_max = opt_cnt - 1, does_combos = 0;
	int dev_id, bind_dev_id, dev_count, kc, is_down, mkey;
	int unbind, bindtype, mask_shift;

	for (i = 0, dev_id = -1, dev_count = 0; i < IN_MAX_DEVS; i++) {
		if (in_get_dev_name(i, 1, 0) != NULL) {
			dev_count++;
			if (dev_id < 0)
				dev_id = i;
		}
	}

	if (dev_id == -1) {
		lprintf("no devs, can't do config\n");
		return;
	}

	dev_id = -1; // show all
	mask_shift = 0;
	if (player_idx == 1)
		mask_shift = 16;
	bindtype = player_idx >= 0 ? IN_BINDTYPE_PLAYER12 : IN_BINDTYPE_EMU;

	for (;;)
	{
		draw_key_config(opts, opt_cnt, player_idx, sel, dev_id, dev_count, 0);
		mkey = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT
				|PBTN_MBACK|PBTN_MOK|PBTN_MA2, NULL, 100);
		switch (mkey) {
			case PBTN_UP:   sel--; if (sel < 0) sel = menu_sel_max; continue;
			case PBTN_DOWN: sel++; if (sel > menu_sel_max) sel = 0; continue;
			case PBTN_LEFT:
				for (i = 0, dev_id--; i < IN_MAX_DEVS + 1; i++, dev_id--) {
					if (dev_id < -1)
						dev_id = IN_MAX_DEVS - 1;
					if (dev_id == -1 || in_get_dev_name(dev_id, 0, 0) != NULL)
						break;
				}
				continue;
			case PBTN_RIGHT:
				for (i = 0, dev_id++; i < IN_MAX_DEVS; i++, dev_id++) {
					if (dev_id >= IN_MAX_DEVS)
						dev_id = -1;
					if (dev_id == -1 || in_get_dev_name(dev_id, 0, 0) != NULL)
						break;
				}
				continue;
			case PBTN_MBACK:
				return;
			case PBTN_MOK:
				if (sel >= opt_cnt)
					return;
				while (in_menu_wait_any(NULL, 30) & PBTN_MOK)
					;
				break;
			case PBTN_MA2:
				in_unbind_all(dev_id, opts[sel].mask << mask_shift, bindtype);
				continue;
			default:continue;
		}

		draw_key_config(opts, opt_cnt, player_idx, sel, dev_id, dev_count, 1);

		/* wait for some up event */
		for (is_down = 1; is_down; )
			kc = in_update_keycode(&bind_dev_id, &is_down, NULL, -1);

		i = count_bound_keys(bind_dev_id, opts[sel].mask << mask_shift, bindtype);
		unbind = (i > 0);

		/* allow combos if device supports them */
		in_get_config(bind_dev_id, IN_CFG_DOES_COMBOS, &does_combos);
		if (i == 1 && bindtype == IN_BINDTYPE_EMU && does_combos)
			unbind = 0;

		if (unbind)
			in_unbind_all(bind_dev_id, opts[sel].mask << mask_shift, bindtype);

		in_bind_key(bind_dev_id, kc, opts[sel].mask << mask_shift, bindtype, 0);
	}
}