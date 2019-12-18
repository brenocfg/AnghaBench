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
 int FALSE ; 
 int /*<<< orphan*/  LoadExecPS2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_flushlog () ; 
 scalar_t__ MONITOR_Run () ; 
 int /*<<< orphan*/  SifExitRpc () ; 
 int /*<<< orphan*/  Sound_Exit () ; 
 int TRUE ; 
 int /*<<< orphan*/  fioExit () ; 
 int /*<<< orphan*/  timer_shutdown () ; 

int PLATFORM_Exit(int run_monitor)
{
	// TODO: shutdown graphics mode
	Log_flushlog();
#if 0
	if (run_monitor && MONITOR_Run()) {
		// TODO: reinitialize graphics mode
		return TRUE;
	}
#endif
#ifdef USE_TIMERS
	timer_shutdown();
#endif
/* TODO Sound_Exit should not be called here! It only stays here now because
   the next step restarts the PS2 without ever returning from this function to
   Atari800_Exit, so the call to Sound_Exit located in the latter function is
   never invoked. So, should the LoadExecPS2call below get removed, so should
   this call to Sound_Exit. */
#ifdef SOUND
	Sound_Exit();
#endif
//zzz temp exit procedure
//Hard coded to go back to ulaunch
	fioExit();
	SifExitRpc();
	LoadExecPS2("mc0:/BOOT/BOOT.ELF", 0, NULL);
//zzz end
	return FALSE;
}