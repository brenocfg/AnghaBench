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
struct snd_sb {int open; int /*<<< orphan*/  midi_input_lock; int /*<<< orphan*/  midi_substream_input; struct snd_rawmidi* rmidi; } ;
struct snd_rawmidi {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_AVAIL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  SBP (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int SB_OPEN_MIDI_INPUT_TRIGGER ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

irqreturn_t snd_sb8dsp_midi_interrupt(struct snd_sb *chip)
{
	struct snd_rawmidi *rmidi;
	int max = 64;
	char byte;

	if (!chip)
		return IRQ_NONE;
	
	rmidi = chip->rmidi;
	if (!rmidi) {
		inb(SBP(chip, DATA_AVAIL));	/* ack interrupt */
		return IRQ_NONE;
	}

	spin_lock(&chip->midi_input_lock);
	while (max-- > 0) {
		if (inb(SBP(chip, DATA_AVAIL)) & 0x80) {
			byte = inb(SBP(chip, READ));
			if (chip->open & SB_OPEN_MIDI_INPUT_TRIGGER) {
				snd_rawmidi_receive(chip->midi_substream_input, &byte, 1);
			}
		}
	}
	spin_unlock(&chip->midi_input_lock);
	return IRQ_HANDLED;
}