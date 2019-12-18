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
struct TYPE_2__ {int Frameskip; int EmuOpt; } ;

/* Variables and functions */
 void* PsndOut ; 
 int /*<<< orphan*/  PsndRerate (int) ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  emu_status_msg (char*) ; 

void emu_set_fastforward(int set_on)
{
	static void *set_PsndOut = NULL;
	static int set_Frameskip, set_EmuOpt, is_on = 0;

	if (set_on && !is_on) {
		set_PsndOut = PsndOut;
		set_Frameskip = currentConfig.Frameskip;
		set_EmuOpt = currentConfig.EmuOpt;
		PsndOut = NULL;
		currentConfig.Frameskip = 8;
		currentConfig.EmuOpt &= ~4;
		currentConfig.EmuOpt |= 0x40000;
		is_on = 1;
		emu_status_msg("FAST FORWARD");
	}
	else if (!set_on && is_on) {
		PsndOut = set_PsndOut;
		currentConfig.Frameskip = set_Frameskip;
		currentConfig.EmuOpt = set_EmuOpt;
		PsndRerate(1);
		is_on = 0;
	}
}