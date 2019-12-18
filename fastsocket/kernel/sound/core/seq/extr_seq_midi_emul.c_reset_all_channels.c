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
struct snd_midi_channel_set {int max_channels; struct snd_midi_channel* channels; } ;
struct snd_midi_channel {int gm_rpn_pitch_bend_range; int drum_channel; scalar_t__ gm_rpn_coarse_tuning; scalar_t__ gm_rpn_fine_tuning; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_midi_reset_controllers (struct snd_midi_channel*) ; 

__attribute__((used)) static void
reset_all_channels(struct snd_midi_channel_set *chset)
{
	int ch;
	for (ch = 0; ch < chset->max_channels; ch++) {
		struct snd_midi_channel *chan = chset->channels + ch;
		snd_midi_reset_controllers(chan);
		chan->gm_rpn_pitch_bend_range = 256; /* 2 semitones */
		chan->gm_rpn_fine_tuning = 0;
		chan->gm_rpn_coarse_tuning = 0;

		if (ch == 9)
			chan->drum_channel = 1;
		else
			chan->drum_channel = 0;
	}
}