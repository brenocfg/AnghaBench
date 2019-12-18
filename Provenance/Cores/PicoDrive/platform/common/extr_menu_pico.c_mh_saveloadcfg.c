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
#define  MA_OPT_LOADCFG 130 
#define  MA_OPT_SAVECFG 129 
#define  MA_OPT_SAVECFG_GAME 128 
 int PBTN_LEFT ; 
 int PBTN_RIGHT ; 
 int config_slot ; 
 int config_slot_current ; 
 int /*<<< orphan*/  e_menu_options ; 
 int emu_read_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emu_write_config (int) ; 
 int /*<<< orphan*/  me_enable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  menu_update_msg (char*) ; 
 int /*<<< orphan*/ * rom_fname_loaded ; 

__attribute__((used)) static int mh_saveloadcfg(int id, int keys)
{
	int ret;

	if (keys & (PBTN_LEFT|PBTN_RIGHT)) { // multi choice
		config_slot += (keys & PBTN_LEFT) ? -1 : 1;
		if (config_slot < 0) config_slot = 9;
		else if (config_slot > 9) config_slot = 0;
		me_enable(e_menu_options, MA_OPT_LOADCFG, config_slot != config_slot_current);
		return 0;
	}

	switch (id) {
	case MA_OPT_SAVECFG:
	case MA_OPT_SAVECFG_GAME:
		if (emu_write_config(id == MA_OPT_SAVECFG_GAME ? 1 : 0))
			menu_update_msg("config saved");
		else
			menu_update_msg("failed to write config");
		break;
	case MA_OPT_LOADCFG:
		ret = emu_read_config(rom_fname_loaded, 1);
		if (!ret) ret = emu_read_config(NULL, 1);
		if (ret)  menu_update_msg("config loaded");
		else      menu_update_msg("failed to load config");
		break;
	default:
		return 0;
	}

	return 1;
}