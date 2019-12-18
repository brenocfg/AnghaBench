#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct snd_sb {int open; int /*<<< orphan*/  open_lock; TYPE_2__ midi_timer; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_4__ {struct snd_sb* private_data; } ;

/* Variables and functions */
 int SB_OPEN_MIDI_OUTPUT_TRIGGER ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_output_timer ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_output_write (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sb8dsp_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct snd_sb *chip;

	chip = substream->rmidi->private_data;
	spin_lock_irqsave(&chip->open_lock, flags);
	if (up) {
		if (!(chip->open & SB_OPEN_MIDI_OUTPUT_TRIGGER)) {
			init_timer(&chip->midi_timer);
			chip->midi_timer.function = snd_sb8dsp_midi_output_timer;
			chip->midi_timer.data = (unsigned long) substream;
			chip->midi_timer.expires = 1 + jiffies;
			add_timer(&chip->midi_timer);
			chip->open |= SB_OPEN_MIDI_OUTPUT_TRIGGER;
		}
	} else {
		if (chip->open & SB_OPEN_MIDI_OUTPUT_TRIGGER) {
			chip->open &= ~SB_OPEN_MIDI_OUTPUT_TRIGGER;
		}
	}
	spin_unlock_irqrestore(&chip->open_lock, flags);

	if (up)
		snd_sb8dsp_midi_output_write(substream);
}