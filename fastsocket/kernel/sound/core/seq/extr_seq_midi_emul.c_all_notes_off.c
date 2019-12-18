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
struct snd_midi_op {int /*<<< orphan*/  note_off; } ;
struct snd_midi_channel {scalar_t__* note; } ;

/* Variables and functions */
 scalar_t__ SNDRV_MIDI_NOTE_ON ; 
 int /*<<< orphan*/  note_off (struct snd_midi_op*,void*,struct snd_midi_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
all_notes_off(struct snd_midi_op *ops, void *drv, struct snd_midi_channel *chan)
{
	int n;

	if (! ops->note_off)
		return;
	for (n = 0; n < 128; n++) {
		if (chan->note[n] == SNDRV_MIDI_NOTE_ON)
			note_off(ops, drv, chan, n, 0);
	}
}