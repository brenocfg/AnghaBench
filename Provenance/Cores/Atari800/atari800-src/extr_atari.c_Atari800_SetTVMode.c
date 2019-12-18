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
struct TYPE_2__ {int sample_size; int /*<<< orphan*/  channels; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARTIFACT_SetTVMode (int) ; 
 int Atari800_tv_mode ; 
 int /*<<< orphan*/  Colours_SetVideoSystem (int) ; 
 int /*<<< orphan*/  POKEYSND_BIT16 ; 
 int /*<<< orphan*/  POKEYSND_FREQ_17_EXACT ; 
 int /*<<< orphan*/  POKEYSND_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTVModeMenuItem (int) ; 
 int /*<<< orphan*/  Sound_Reinit () ; 
 TYPE_1__ Sound_out ; 
 int /*<<< orphan*/  VIDEOMODE_SetVideoSystem (int) ; 

void Atari800_SetTVMode(int mode)
{
	if (mode != Atari800_tv_mode) {
		Atari800_tv_mode = mode;
#if !defined(BASIC) && !defined(CURSES_BASIC)
		Colours_SetVideoSystem(mode);
		ARTIFACT_SetTVMode(mode);
#endif
#if SUPPORTS_CHANGE_VIDEOMODE
		VIDEOMODE_SetVideoSystem(mode);
#endif
#ifdef SOUND
#ifdef SOUND_THIN_API
		POKEYSND_Init(POKEYSND_FREQ_17_EXACT, Sound_out.freq, Sound_out.channels, Sound_out.sample_size == 2 ? POKEYSND_BIT16 : 0);
#elif defined(SUPPORTS_SOUND_REINIT)
		Sound_Reinit();
#endif /* defined(SUPPORTS_SOUND_REINIT) */
#endif /* SOUND */
#if defined(DIRECTX)
		SetTVModeMenuItem(mode);
#endif
	}
}