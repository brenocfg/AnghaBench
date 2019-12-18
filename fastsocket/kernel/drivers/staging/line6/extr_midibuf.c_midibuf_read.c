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
struct MidiBuffer {int size; size_t pos_read; int* buf; int command_prev; scalar_t__ full; int /*<<< orphan*/  split; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 
 int midibuf_bytes_used (struct MidiBuffer*) ; 
 scalar_t__ midibuf_is_empty (struct MidiBuffer*) ; 
 int midibuf_message_length (int) ; 

int midibuf_read(struct MidiBuffer *this, unsigned char *data, int length)
{
	int bytes_used;
	int length1, length2;
	int command;
	int midi_length;
	int repeat = 0;
	int i;

	/* we need to be able to store at least a 3 byte MIDI message */
	if (length < 3)
		return -EINVAL;

	if (midibuf_is_empty(this))
		return 0;

	bytes_used = midibuf_bytes_used(this);

	if (length > bytes_used)
		length = bytes_used;

	length1 = this->size - this->pos_read;

	/* check MIDI command length */
	command = this->buf[this->pos_read];

	if (command & 0x80) {
		midi_length = midibuf_message_length(command);
		this->command_prev = command;
	} else {
		if (this->command_prev > 0) {
			int midi_length_prev = midibuf_message_length(this->command_prev);

			if (midi_length_prev > 0) {
				midi_length = midi_length_prev - 1;
				repeat = 1;
			} else
				midi_length = -1;
		} else
			midi_length = -1;
	}

	if (midi_length < 0) {
		/* search for end of message */
		if (length < length1) {
			/* no buffer wraparound */
			for (i = 1; i < length; ++i)
				if (this->buf[this->pos_read + i] & 0x80)
					break;

			midi_length = i;
		} else {
			/* buffer wraparound */
			length2 = length - length1;

			for (i = 1; i < length1; ++i)
				if (this->buf[this->pos_read + i] & 0x80)
					break;

			if (i < length1)
				midi_length = i;
			else {
				for (i = 0; i < length2; ++i)
					if (this->buf[i] & 0x80)
						break;

				midi_length = length1 + i;
			}
		}

		if (midi_length == length)
			midi_length = -1;  /* end of message not found */
	}

	if (midi_length < 0) {
		if (!this->split)
			return 0;  /* command is not yet complete */
	} else {
		if (length < midi_length)
			return 0;  /* command is not yet complete */

		length = midi_length;
	}

	if (length < length1) {
		/* no buffer wraparound */
		memcpy(data + repeat, this->buf + this->pos_read, length);
		this->pos_read += length;
	} else {
		/* buffer wraparound */
		length2 = length - length1;
		memcpy(data + repeat, this->buf + this->pos_read, length1);
		memcpy(data + repeat + length1, this->buf, length2);
		this->pos_read = length2;
	}

	if (repeat)
		data[0] = this->command_prev;

	this->full = 0;
	return length + repeat;
}