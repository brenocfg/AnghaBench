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
 int /*<<< orphan*/  FrameworkAudio_SetPause (int) ; 
 int Framework_PollGetButtons () ; 
 int /*<<< orphan*/  GetTickCount () ; 
 int PBTN_PLAY ; 
 int PBTN_STOP ; 
 int PicoOpt ; 
 int /*<<< orphan*/ * PicoStateProgressCB ; 
 int /*<<< orphan*/ * PsndOut ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  blit (char*,char*) ; 
 int /*<<< orphan*/  clearArea (int /*<<< orphan*/ ) ; 
 TYPE_1__ currentConfig ; 
 scalar_t__ emu_check_save_file (int) ; 
 int /*<<< orphan*/  emu_save_load_game (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emu_stateCb ; 
 int /*<<< orphan*/ * fb_lock (int) ; 
 int /*<<< orphan*/ * giz_screen ; 
 int /*<<< orphan*/  noticeMsg ; 
 int /*<<< orphan*/  noticeMsgTime ; 
 int /*<<< orphan*/  osd_text (int,int,char*) ; 
 int reset_timing ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int state_slot ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vidResetMode () ; 

__attribute__((used)) static void RunEvents(unsigned int which)
{
	if (which & 0x1800) // save or load (but not both)
	{
		int do_it = 1;

		if (PsndOut != NULL)
			FrameworkAudio_SetPause(1);
		if (giz_screen == NULL)
			giz_screen = fb_lock(1);
		if ( emu_check_save_file(state_slot) &&
				(( (which & 0x1000) && (currentConfig.EmuOpt & 0x800)) || // load
				 (!(which & 0x1000) && (currentConfig.EmuOpt & 0x200))) ) // save
		{
			int keys;
			blit("", (which & 0x1000) ? "LOAD STATE? (PLAY=yes, STOP=no)" : "OVERWRITE SAVE? (PLAY=yes, STOP=no)");
			while( !((keys = Framework_PollGetButtons()) & (PBTN_PLAY|PBTN_STOP)) )
				Sleep(50);
			if (keys & PBTN_STOP) do_it = 0;
			while(  ((keys = Framework_PollGetButtons()) & (PBTN_PLAY|PBTN_STOP)) ) // wait for release
				Sleep(50);
			clearArea(0);
		}

		if (do_it)
		{
			osd_text(4, 232, (which & 0x1000) ? "LOADING GAME" : "SAVING GAME");
			PicoStateProgressCB = emu_stateCb;
			emu_save_load_game((which & 0x1000) >> 12, 0);
			PicoStateProgressCB = NULL;
			Sleep(0);
		}

		if (PsndOut != NULL)
			FrameworkAudio_SetPause(0);
		reset_timing = 1;
	}
	if (which & 0x0400) // switch renderer
	{
		if (PicoOpt&0x10) { PicoOpt&=~0x10; currentConfig.EmuOpt |=  0x80; }
		else              { PicoOpt|= 0x10; currentConfig.EmuOpt &= ~0x80; }

		vidResetMode();

		if (PicoOpt&0x10) {
			strcpy(noticeMsg, " 8bit fast renderer");
		} else if (currentConfig.EmuOpt&0x80) {
			strcpy(noticeMsg, "16bit accurate renderer");
		} else {
			strcpy(noticeMsg, " 8bit accurate renderer");
		}

		noticeMsgTime = GetTickCount();
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
		sprintf(noticeMsg, "SAVE SLOT %i [%s]", state_slot, emu_check_save_file(state_slot) ? "USED" : "FREE");
		noticeMsgTime = GetTickCount();
	}
}