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
struct snd_midi_channel {int* control; int /*<<< orphan*/  drum_channel; } ;
struct TYPE_2__ {int midi_mode; } ;
struct snd_emux_port {TYPE_1__ chset; } ;

/* Variables and functions */
 size_t MIDI_CTL_LSB_BANK ; 
 size_t MIDI_CTL_MSB_BANK ; 
#define  SNDRV_MIDI_MODE_GS 129 
#define  SNDRV_MIDI_MODE_XG 128 

__attribute__((used)) static int
get_bank(struct snd_emux_port *port, struct snd_midi_channel *chan)
{
	int val;

	switch (port->chset.midi_mode) {
	case SNDRV_MIDI_MODE_XG:
		val = chan->control[MIDI_CTL_MSB_BANK];
		if (val == 127)
			return 128; /* return drum bank */
		return chan->control[MIDI_CTL_LSB_BANK];

	case SNDRV_MIDI_MODE_GS:
		if (chan->drum_channel)
			return 128;
		/* ignore LSB (bank map) */
		return chan->control[MIDI_CTL_MSB_BANK];
		
	default:
		if (chan->drum_channel)
			return 128;
		return chan->control[MIDI_CTL_MSB_BANK];
	}
}