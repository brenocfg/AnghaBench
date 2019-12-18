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
#define  PGS_Menu 133 
#define  PGS_Quit 132 
#define  PGS_ReloadRom 131 
#define  PGS_RestartRun 130 
#define  PGS_Running 129 
#define  PGS_TrayMenu 128 
 int /*<<< orphan*/  emu_finish () ; 
 int /*<<< orphan*/  emu_init () ; 
 int /*<<< orphan*/  emu_loop () ; 
 int /*<<< orphan*/  emu_prep_defconfig () ; 
 int /*<<< orphan*/  emu_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ emu_reload_rom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_save_load_game (int,int /*<<< orphan*/ ) ; 
 int engineState ; 
 char** g_argv ; 
 int /*<<< orphan*/  in_init () ; 
 scalar_t__ load_state_slot ; 
 int /*<<< orphan*/  menu_init () ; 
 int /*<<< orphan*/  menu_loop () ; 
 int /*<<< orphan*/  menu_loop_tray () ; 
 int /*<<< orphan*/  parse_cmd_line (int,char**) ; 
 int /*<<< orphan*/  plat_early_init () ; 
 int /*<<< orphan*/  plat_finish () ; 
 int /*<<< orphan*/  plat_init () ; 
 int /*<<< orphan*/  plat_target_finish () ; 
 int /*<<< orphan*/  plat_target_init () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rom_fname_reload ; 
 scalar_t__ state_slot ; 

int main(int argc, char *argv[])
{
	g_argv = argv;

	plat_early_init();

	in_init();
	//in_probe();

	plat_target_init();
	plat_init();

	emu_prep_defconfig(); // depends on input
	emu_read_config(NULL, 0);

	emu_init();
	menu_init();

	engineState = PGS_Menu;

	if (argc > 1)
		parse_cmd_line(argc, argv);

	if (engineState == PGS_ReloadRom)
	{
		if (emu_reload_rom(rom_fname_reload)) {
			engineState = PGS_Running;
			if (load_state_slot >= 0) {
				state_slot = load_state_slot;
				emu_save_load_game(1, 0);
			}
		}
	}

	for (;;)
	{
		switch (engineState)
		{
			case PGS_Menu:
				menu_loop();
				break;

			case PGS_TrayMenu:
				menu_loop_tray();
				break;

			case PGS_ReloadRom:
				if (emu_reload_rom(rom_fname_reload))
					engineState = PGS_Running;
				else {
					printf("PGS_ReloadRom == 0\n");
					engineState = PGS_Menu;
				}
				break;

			case PGS_RestartRun:
				engineState = PGS_Running;
				/* vvv fallthrough */

			case PGS_Running:
				emu_loop();
				break;

			case PGS_Quit:
				goto endloop;

			default:
				printf("engine got into unknown state (%i), exitting\n", engineState);
				goto endloop;
		}
	}

	endloop:

	emu_finish();
	plat_finish();
	plat_target_finish();

	return 0;
}