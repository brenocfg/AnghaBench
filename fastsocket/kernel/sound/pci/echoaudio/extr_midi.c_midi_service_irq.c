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
typedef  scalar_t__ u8 ;
struct echoaudio {scalar_t__* midi_buffer; TYPE_1__* comm_page; } ;
struct TYPE_2__ {int /*<<< orphan*/ * midi_input; } ;

/* Variables and functions */
 short MIDI_IN_BUFFER_SIZE ; 
 scalar_t__ MIDI_IN_SKIP_DATA ; 
 short le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mtc_process_data (struct echoaudio*,short) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int midi_service_irq(struct echoaudio *chip)
{
	short int count, midi_byte, i, received;

	/* The count is at index 0, followed by actual data */
	count = le16_to_cpu(chip->comm_page->midi_input[0]);

	if (snd_BUG_ON(count >= MIDI_IN_BUFFER_SIZE))
		return 0;

	/* Get the MIDI data from the comm page */
	i = 1;
	received = 0;
	for (i = 1; i <= count; i++) {
		/* Get the MIDI byte */
		midi_byte = le16_to_cpu(chip->comm_page->midi_input[i]);

		/* Parse the incoming MIDI stream. The incoming MIDI data
		consists of MIDI bytes and timestamps for the MIDI time code
		0xF1 bytes. mtc_process_data() is a little state machine that
		parses the stream. If you get MIDI_IN_SKIP_DATA back, then
		this is a timestamp byte, not a MIDI byte, so don't store it
		in the MIDI input buffer. */
		if (mtc_process_data(chip, midi_byte) == MIDI_IN_SKIP_DATA)
			continue;

		chip->midi_buffer[received++] = (u8)midi_byte;
	}

	return received;
}