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
struct TYPE_2__ {int EmuOpt; } ;

/* Variables and functions */
 int PBTN_CIRCLE ; 
 int PBTN_X ; 
 int POPT_ALT_RENDERER ; 
 int PicoOpt ; 
 int /*<<< orphan*/ * PicoStateProgressCB ; 
 int /*<<< orphan*/  blit2 (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearArea (int /*<<< orphan*/ ) ; 
 TYPE_1__ currentConfig ; 
 scalar_t__ emu_check_save_file (int) ; 
 int /*<<< orphan*/ * emu_msg_cb ; 
 int /*<<< orphan*/  emu_save_load_game (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_status_msg (char*,...) ; 
 int /*<<< orphan*/  osd_text (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_msleep (int) ; 
 int psp_pad_read (int) ; 
 int reset_timing ; 
 int /*<<< orphan*/  sceGuSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int state_slot ; 
 int /*<<< orphan*/  vidResetMode () ; 

__attribute__((used)) static void RunEvents(unsigned int which)
{
	if (which & 0x1800) // save or load (but not both)
	{
		int do_it = 1;

		if ( emu_check_save_file(state_slot) &&
				(( (which & 0x1000) && (currentConfig.EmuOpt & 0x800)) || // load
				 (!(which & 0x1000) && (currentConfig.EmuOpt & 0x200))) ) // save
		{
			int keys;
			sceGuSync(0,0);
			blit2("", (which & 0x1000) ? "LOAD STATE? (X=yes, O=no)" : "OVERWRITE SAVE? (X=yes, O=no)", 0);
			while( !((keys = psp_pad_read(1)) & (PBTN_X|PBTN_CIRCLE)) )
				psp_msleep(50);
			if (keys & PBTN_CIRCLE) do_it = 0;
			while(  ((keys = psp_pad_read(1)) & (PBTN_X|PBTN_CIRCLE)) ) // wait for release
				psp_msleep(50);
			clearArea(0);
		}

		if (do_it)
		{
			osd_text(4, (which & 0x1000) ? "LOADING GAME" : "SAVING GAME", 1, 0);
			PicoStateProgressCB = emu_msg_cb;
			emu_save_load_game((which & 0x1000) >> 12, 0);
			PicoStateProgressCB = NULL;
			psp_msleep(0);
		}

		reset_timing = 1;
	}
	if (which & 0x0400) // switch renderer
	{
		if (PicoOpt&0x10) { PicoOpt&=~0x10; currentConfig.EmuOpt |=  0x80; }
		else              { PicoOpt|= 0x10; currentConfig.EmuOpt &= ~0x80; }

		vidResetMode();

		if (PicoOpt & POPT_ALT_RENDERER)
			emu_status_msg("fast renderer");
		else if (currentConfig.EmuOpt&0x80)
			emu_status_msg("accurate renderer");
	}
	if (which & 0x0300)
	{
		if(which&0x0200) {
			state_slot -= 1;
			if(state_slot < 0) state_slot = 9;
		} else {
			state_slot += 1;
			if(state_slot > 9) state_slot = 0;
		}
		emu_status_msg("SAVE SLOT %i [%s]", state_slot,
			emu_check_save_file(state_slot) ? "USED" : "FREE");
	}
}