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
struct TYPE_2__ {int volume; } ;

/* Variables and functions */
 unsigned int CONFIGURABLE_KEYS ; 
 int /*<<< orphan*/  FrameworkAudio_SetVolume (int,int) ; 
 unsigned int Framework_PollGetButtons () ; 
 int /*<<< orphan*/  GetTickCount () ; 
 unsigned int PBTN_HOME ; 
 int /*<<< orphan*/  PGS_Menu ; 
 unsigned int* PicoPad ; 
 int /*<<< orphan*/ * PsndOut ; 
 int /*<<< orphan*/  RunEvents (unsigned int) ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  emu_DoTurbo (unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  emu_updateMovie () ; 
 int /*<<< orphan*/  engineState ; 
 scalar_t__ movie_data ; 
 int /*<<< orphan*/  noticeMsg ; 
 int /*<<< orphan*/  noticeMsgTime ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void updateKeys(void)
{
	unsigned int keys, allActions[2] = { 0, 0 }, events;
	static unsigned int prevEvents = 0;
	int i;

	/* FIXME: port to input fw, merge with emu.c:emu_update_input() */
	keys = Framework_PollGetButtons();
	if (keys & PBTN_HOME)
		engineState = PGS_Menu;

	keys &= CONFIGURABLE_KEYS;

	PicoPad[0] = allActions[0] & 0xfff;
	PicoPad[1] = allActions[1] & 0xfff;

	if (allActions[0] & 0x7000) emu_DoTurbo(&PicoPad[0], allActions[0]);
	if (allActions[1] & 0x7000) emu_DoTurbo(&PicoPad[1], allActions[1]);

	events = (allActions[0] | allActions[1]) >> 16;

	// volume is treated in special way and triggered every frame
	if ((events & 0x6000) && PsndOut != NULL)
	{
		int vol = currentConfig.volume;
		if (events & 0x2000) {
			if (vol < 100) vol++;
		} else {
			if (vol >   0) vol--;
		}
		FrameworkAudio_SetVolume(vol, vol);
		sprintf(noticeMsg, "VOL: %02i ", vol);
		noticeMsgTime = GetTickCount();
		currentConfig.volume = vol;
	}

	events &= ~prevEvents;
	if (events) RunEvents(events);
	if (movie_data) emu_updateMovie();

	prevEvents = (allActions[0] | allActions[1]) >> 16;
}