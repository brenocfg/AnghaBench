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
struct snd_midi_channel_set {int /*<<< orphan*/  gs_reverb_mode; int /*<<< orphan*/  gs_chorus_mode; } ;
struct snd_emux {struct snd_emu8000* hw; } ;
struct snd_emu8000 {int /*<<< orphan*/  reverb_mode; int /*<<< orphan*/  chorus_mode; } ;

/* Variables and functions */
#define  SNDRV_MIDI_SYSEX_GS_CHORUS_MODE 129 
#define  SNDRV_MIDI_SYSEX_GS_REVERB_MODE 128 
 int /*<<< orphan*/  snd_emu8000_update_chorus_mode (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_update_reverb_mode (struct snd_emu8000*) ; 

__attribute__((used)) static void
sysex(struct snd_emux *emu, char *buf, int len, int parsed, struct snd_midi_channel_set *chset)
{
	struct snd_emu8000 *hw;

	hw = emu->hw;

	switch (parsed) {
	case SNDRV_MIDI_SYSEX_GS_CHORUS_MODE:
		hw->chorus_mode = chset->gs_chorus_mode;
		snd_emu8000_update_chorus_mode(hw);
		break;

	case SNDRV_MIDI_SYSEX_GS_REVERB_MODE:
		hw->reverb_mode = chset->gs_reverb_mode;
		snd_emu8000_update_reverb_mode(hw);
		break;
	}
}