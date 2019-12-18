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
struct snd_card {int dummy; } ;
struct seq_midisynth {int device; int subdevice; struct snd_card* card; int /*<<< orphan*/  parser; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_MIDI_EVENT_BUF ; 
 scalar_t__ snd_midi_event_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_seq_midisynth_new(struct seq_midisynth *msynth,
				 struct snd_card *card,
				 int device,
				 int subdevice)
{
	if (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &msynth->parser) < 0)
		return -ENOMEM;
	msynth->card = card;
	msynth->device = device;
	msynth->subdevice = subdevice;
	return 0;
}