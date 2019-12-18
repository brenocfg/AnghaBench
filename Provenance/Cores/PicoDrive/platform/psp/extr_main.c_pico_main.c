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
#define  PGS_Menu 134 
#define  PGS_Quit 133 
#define  PGS_ReloadRom 132 
#define  PGS_RestartRun 131 
#define  PGS_Running 130 
#define  PGS_SuspendWake 129 
#define  PGS_Suspending 128 
 int /*<<< orphan*/  PicoConfigFile ; 
 int /*<<< orphan*/  config_readlrom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_Deinit () ; 
 int /*<<< orphan*/  emu_HandleResume () ; 
 int /*<<< orphan*/  emu_Init () ; 
 int /*<<< orphan*/  emu_ReadConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_prepareDefaultConfig () ; 
 int /*<<< orphan*/  emu_reload_rom (int /*<<< orphan*/ ) ; 
 int engineState ; 
 int engineStateSuspend ; 
 int /*<<< orphan*/  gprof_cleanup () ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int /*<<< orphan*/  menu_init () ; 
 int /*<<< orphan*/  menu_loop () ; 
 int /*<<< orphan*/  mp3_deinit () ; 
 int /*<<< orphan*/  mp3_last_error ; 
 int /*<<< orphan*/  pemu_loop () ; 
 int /*<<< orphan*/  psp_finish () ; 
 int /*<<< orphan*/  psp_init () ; 
 int /*<<< orphan*/  psp_resume_suspend () ; 
 int /*<<< orphan*/  psp_unhandled_suspend ; 
 int /*<<< orphan*/  psp_wait_suspend () ; 
 int /*<<< orphan*/  rom_fname_loaded ; 
 int /*<<< orphan*/  rom_fname_reload ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pico_main(void)
{
	psp_init();

	emu_prepareDefaultConfig();
	emu_ReadConfig(0, 0);
	config_readlrom(PicoConfigFile);

	emu_Init();
	menu_init();
	// moved to emu_Loop(), after CPU clock change..
	//mp3_init();

	engineState = PGS_Menu;

	for (;;)
	{
		switch (engineState)
		{
			case PGS_Menu:
#ifndef GPROF
				menu_loop();
#else
				strcpy(rom_fname_reload, rom_fname_loaded);
				engineState = PGS_ReloadRom;
#endif
				break;

			case PGS_ReloadRom:
				if (emu_reload_rom(rom_fname_reload)) {
					engineState = PGS_Running;
					if (mp3_last_error != 0)
						engineState = PGS_Menu; // send to menu to display mp3 error
				} else {
					lprintf("PGS_ReloadRom == 0\n");
					engineState = PGS_Menu;
				}
				break;

			case PGS_Suspending:
				while (engineState == PGS_Suspending)
					psp_wait_suspend();
				break;

			case PGS_SuspendWake:
				psp_unhandled_suspend = 0;
				psp_resume_suspend();
				emu_HandleResume();
				engineState = engineStateSuspend;
				break;

			case PGS_RestartRun:
				engineState = PGS_Running;

			case PGS_Running:
				if (psp_unhandled_suspend) {
					psp_unhandled_suspend = 0;
					psp_resume_suspend();
					emu_HandleResume();
					break;
				}
				pemu_loop();
#ifdef GPROF
				goto endloop;
#endif
				break;

			case PGS_Quit:
				goto endloop;

			default:
				lprintf("engine got into unknown state (%i), exitting\n", engineState);
				goto endloop;
		}
	}

	endloop:

	mp3_deinit();
	emu_Deinit();
#ifdef GPROF
	gprof_cleanup();
#endif
#ifndef GCOV
	psp_finish();
#endif

	return 0;
}