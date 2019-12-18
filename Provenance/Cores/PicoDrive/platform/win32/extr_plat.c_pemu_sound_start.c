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
 int DSoundInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int EOPT_EN_SOUND ; 
 int EOPT_EXT_FRMLIMIT ; 
 int /*<<< orphan*/  FrameWnd ; 
 int POPT_EN_STEREO ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PicoWriteSound ; 
 int /*<<< orphan*/  PsndLen ; 
 int /*<<< orphan*/ * PsndOut ; 
 int /*<<< orphan*/  PsndRate ; 
 int /*<<< orphan*/  PsndRerate (int /*<<< orphan*/ ) ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 scalar_t__ sndbuff ; 
 int /*<<< orphan*/  update_sound ; 

void pemu_sound_start(void)
{
	int ret;

	PsndOut = NULL;
	currentConfig.EmuOpt &= ~EOPT_EXT_FRMLIMIT;

	// prepare sound stuff
	if (currentConfig.EmuOpt & EOPT_EN_SOUND)
	{
		PsndRerate(0);

		ret = DSoundInit(FrameWnd, PsndRate, (PicoOpt & POPT_EN_STEREO) ? 1 : 0, PsndLen);
		if (ret != 0) {
			lprintf("dsound init failed\n");
			return;
		}

		PsndOut = (void *)sndbuff;
		PicoWriteSound = update_sound;
		currentConfig.EmuOpt |= EOPT_EXT_FRMLIMIT;
	}
}