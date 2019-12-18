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
struct MidiBuffer {int size; int pos_write; int pos_read; int full; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,int) ; 
 int midibuf_bytes_free (struct MidiBuffer*) ; 
 scalar_t__ midibuf_is_full (struct MidiBuffer*) ; 

int midibuf_write(struct MidiBuffer *this, unsigned char *data, int length)
{
	int bytes_free;
	int length1, length2;
	int skip_active_sense = 0;

	if (midibuf_is_full(this) || (length <= 0))
		return 0;

	/* skip trailing active sense */
	if (data[length - 1] == 0xfe) {
		--length;
		skip_active_sense = 1;
	}

	bytes_free = midibuf_bytes_free(this);

	if (length > bytes_free)
		length = bytes_free;

	if (length > 0) {
		length1 = this->size - this->pos_write;

		if (length < length1) {
			/* no buffer wraparound */
			memcpy(this->buf + this->pos_write, data, length);
			this->pos_write += length;
		} else {
			/* buffer wraparound */
			length2 = length - length1;
			memcpy(this->buf + this->pos_write, data, length1);
			memcpy(this->buf, data + length1, length2);
			this->pos_write = length2;
		}

		if (this->pos_write == this->pos_read)
			this->full = 1;
	}

	return length + skip_active_sense;
}