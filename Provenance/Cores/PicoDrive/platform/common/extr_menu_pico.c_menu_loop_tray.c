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
 int /*<<< orphan*/  IN_CFG_BLOCKING ; 
 int PBTN_MBACK ; 
 int PBTN_MENU ; 
 int PBTN_MOK ; 
 scalar_t__ PGS_RestartRun ; 
 int /*<<< orphan*/  PicoGameLoaded ; 
 int /*<<< orphan*/  e_menu_tray ; 
 scalar_t__ engineState ; 
 int in_menu_wait_any (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_set_config_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  me_loop (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  menu_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plat_video_menu_leave () ; 

int menu_loop_tray(void)
{
	int ret = 1, sel = 0;

	menu_enter(PicoGameLoaded);

	in_set_config_int(0, IN_CFG_BLOCKING, 1);
	me_loop(e_menu_tray, &sel);

	if (engineState != PGS_RestartRun) {
		engineState = PGS_RestartRun;
		ret = 0; /* no CD inserted */
	}

	while (in_menu_wait_any(NULL, 50) & (PBTN_MENU|PBTN_MOK|PBTN_MBACK))
		;
	in_set_config_int(0, IN_CFG_BLOCKING, 0);
	plat_video_menu_leave();

	return ret;
}