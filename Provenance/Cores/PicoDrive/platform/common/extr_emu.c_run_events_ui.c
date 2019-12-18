#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {int confirm_save; } ;

/* Variables and functions */
 int EOPT_CONFIRM_LOAD ; 
 int EOPT_CONFIRM_SAVE ; 
 int /*<<< orphan*/  IN_CFG_BLOCKING ; 
 int PBTN_MBACK ; 
 int PBTN_MOK ; 
 unsigned int PEV_MENU ; 
 unsigned int PEV_SSLOT_NEXT ; 
 unsigned int PEV_SSLOT_PREV ; 
 unsigned int PEV_STATE_LOAD ; 
 unsigned int PEV_STATE_SAVE ; 
 unsigned int PEV_SWITCH_RND ; 
 int /*<<< orphan*/  PGS_Menu ; 
 int /*<<< orphan*/ * PicoStateProgressCB ; 
 TYPE_1__ currentConfig ; 
 scalar_t__ emu_check_save_file (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emu_save_load_game (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_status_msg (char*,int,char*) ; 
 int /*<<< orphan*/  engineState ; 
 char* in_get_key_name (int,int) ; 
 int in_menu_wait_any (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_set_config_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plat_status_msg_busy_first (char*) ; 
 int /*<<< orphan*/ * plat_status_msg_busy_next ; 
 int /*<<< orphan*/  plat_video_toggle_renderer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int state_slot ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void run_events_ui(unsigned int which)
{
	if (which & (PEV_STATE_LOAD|PEV_STATE_SAVE))
	{
		int do_it = 1;
		if ( emu_check_save_file(state_slot, NULL) &&
			(((which & PEV_STATE_LOAD) && (currentConfig.confirm_save & EOPT_CONFIRM_LOAD)) ||
			 ((which & PEV_STATE_SAVE) && (currentConfig.confirm_save & EOPT_CONFIRM_SAVE))) )
		{
			const char *nm;
			char tmp[64];
			int keys, len;

			strcpy(tmp, (which & PEV_STATE_LOAD) ? "LOAD STATE? " : "OVERWRITE SAVE? ");
			len = strlen(tmp);
			nm = in_get_key_name(-1, -PBTN_MOK);
			snprintf(tmp + len, sizeof(tmp) - len, "(%s=yes, ", nm);
			len = strlen(tmp);
			nm = in_get_key_name(-1, -PBTN_MBACK);
			snprintf(tmp + len, sizeof(tmp) - len, "%s=no)", nm);

			plat_status_msg_busy_first(tmp);

			in_set_config_int(0, IN_CFG_BLOCKING, 1);
			while (in_menu_wait_any(NULL, 50) & (PBTN_MOK | PBTN_MBACK))
				;
			while ( !((keys = in_menu_wait_any(NULL, 50)) & (PBTN_MOK | PBTN_MBACK)))
				;
			if (keys & PBTN_MBACK)
				do_it = 0;
			while (in_menu_wait_any(NULL, 50) & (PBTN_MOK | PBTN_MBACK))
				;
			in_set_config_int(0, IN_CFG_BLOCKING, 0);
		}
		if (do_it) {
			plat_status_msg_busy_first((which & PEV_STATE_LOAD) ? "LOADING STATE" : "SAVING STATE");
			PicoStateProgressCB = plat_status_msg_busy_next;
			emu_save_load_game((which & PEV_STATE_LOAD) ? 1 : 0, 0);
			PicoStateProgressCB = NULL;
		}
	}
	if (which & PEV_SWITCH_RND)
	{
		plat_video_toggle_renderer(1, 0);
	}
	if (which & (PEV_SSLOT_PREV|PEV_SSLOT_NEXT))
	{
		if (which & PEV_SSLOT_PREV) {
			state_slot -= 1;
			if (state_slot < 0)
				state_slot = 9;
		} else {
			state_slot += 1;
			if (state_slot > 9)
				state_slot = 0;
		}

		emu_status_msg("SAVE SLOT %i [%s]", state_slot,
			emu_check_save_file(state_slot, NULL) ? "USED" : "FREE");
	}
	if (which & PEV_MENU)
		engineState = PGS_Menu;
}