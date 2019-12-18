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
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int /*<<< orphan*/  MC_TYPE_MC ; 
 int /*<<< orphan*/  PS2KBD_READMODE_RAW ; 
 scalar_t__ PS2KbdInit () ; 
 int /*<<< orphan*/  PS2KbdSetReadmode (int /*<<< orphan*/ ) ; 
 int SifExecModuleBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SifInitRpc (int /*<<< orphan*/ ) ; 
 int SifLoadModule (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SleepThread () ; 
 int /*<<< orphan*/  audsrv ; 
 int /*<<< orphan*/  mcInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2kbd ; 
 int /*<<< orphan*/  size_audsrv ; 
 int /*<<< orphan*/  size_ps2kbd ; 
 int /*<<< orphan*/  size_usbd ; 
 int /*<<< orphan*/  usbd ; 

void loadModules(void)
{
	int ret;
	//init_scr();

	ret = SifLoadModule("rom0:SIO2MAN", 0, NULL);
	if (ret < 0) {
		Log_print("Sio2man loading failed: %d", ret);
		SleepThread();
	}

//	Log_print("mcman");
	SifLoadModule("rom0:MCMAN", 0, NULL);

//	Log_print("mcserv");
	SifLoadModule("rom0:MCSERV", 0, NULL);

//	Log_print("padman");
	ret = SifLoadModule("rom0:PADMAN", 0, NULL);
	if (ret < 0) {
		Log_print("Padman loading failed: %d", ret);
		SleepThread();
	}

	mcInit(MC_TYPE_MC);

//	cdinit(1);
	SifInitRpc(0);

	SifExecModuleBuffer(usbd, size_usbd, 0, NULL, &ret);
	SifExecModuleBuffer(ps2kbd, size_ps2kbd, 0, NULL, &ret);

	if (PS2KbdInit() == 0) {
		Log_print("Failed to Init Keyboard.");
	}
	PS2KbdSetReadmode(PS2KBD_READMODE_RAW);

#ifdef SOUND
	ret = SifLoadModule("rom0:LIBSD", 0, NULL);

	ret = SifExecModuleBuffer(audsrv, size_audsrv, 0, NULL, &ret);
#endif

}