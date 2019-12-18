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
typedef  size_t Colours_preset_t ;

/* Variables and functions */
 scalar_t__ Atari800_TV_NTSC ; 
 scalar_t__ Atari800_tv_mode ; 
 int /*<<< orphan*/  COLOURS_NTSC_RestoreDefaults () ; 
 int /*<<< orphan*/  COLOURS_PAL_RestoreDefaults () ; 
 size_t COLOURS_PRESET_CUSTOM ; 
 int /*<<< orphan*/ * Colours_setup ; 
 int /*<<< orphan*/ * presets ; 

void Colours_SetPreset(Colours_preset_t preset)
{
	if (preset < COLOURS_PRESET_CUSTOM) {
		*Colours_setup = presets[preset];
		if (Atari800_tv_mode == Atari800_TV_NTSC) 
			COLOURS_NTSC_RestoreDefaults();
		else
			COLOURS_PAL_RestoreDefaults();
	}
}