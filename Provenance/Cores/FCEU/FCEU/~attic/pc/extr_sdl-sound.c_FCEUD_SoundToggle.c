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
 int /*<<< orphan*/  FCEUI_SetSoundVolume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCEU_DispMessage (char*) ; 
 int mute ; 
 int /*<<< orphan*/  soundvolume ; 

void FCEUD_SoundToggle(void)
{
	if(mute)
	{
		mute=0;
		FCEUI_SetSoundVolume(soundvolume);
		FCEU_DispMessage("Sound mute off.");
	}
	else
	{
		mute=1;
		FCEUI_SetSoundVolume(0);
		FCEU_DispMessage("Sound mute on.");
	}
}