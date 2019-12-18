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
typedef  int uint8_t ;
struct urb {int* transfer_buffer; int transfer_buffer_length; } ;
struct snd_usb_midi_out_endpoint {int max_transfer; TYPE_1__* ports; } ;
struct snd_rawmidi_substream {int dummy; } ;
struct TYPE_2__ {scalar_t__ active; struct snd_rawmidi_substream* substream; } ;

/* Variables and functions */
 int MAX_AKAI_SYSEX_LEN ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static void snd_usbmidi_akai_output(struct snd_usb_midi_out_endpoint *ep,
				    struct urb *urb)
{
	uint8_t *msg;
	int pos, end, count, buf_end;
	uint8_t tmp[MAX_AKAI_SYSEX_LEN];
	struct snd_rawmidi_substream *substream = ep->ports[0].substream;

	if (!ep->ports[0].active)
		return;

	msg = urb->transfer_buffer + urb->transfer_buffer_length;
	buf_end = ep->max_transfer - MAX_AKAI_SYSEX_LEN - 1;

	/* only try adding more data when there's space for at least 1 SysEx */
	while (urb->transfer_buffer_length < buf_end) {
		count = snd_rawmidi_transmit_peek(substream,
						  tmp, MAX_AKAI_SYSEX_LEN);
		if (!count) {
			ep->ports[0].active = 0;
			return;
		}
		/* try to skip non-SysEx data */
		for (pos = 0; pos < count && tmp[pos] != 0xF0; pos++)
			;

		if (pos > 0) {
			snd_rawmidi_transmit_ack(substream, pos);
			continue;
		}

		/* look for the start or end marker */
		for (end = 1; end < count && tmp[end] < 0xF0; end++)
			;

		/* next SysEx started before the end of current one */
		if (end < count && tmp[end] == 0xF0) {
			/* it's incomplete - drop it */
			snd_rawmidi_transmit_ack(substream, end);
			continue;
		}
		/* SysEx complete */
		if (end < count && tmp[end] == 0xF7) {
			/* queue it, ack it, and get the next one */
			count = end + 1;
			msg[0] = 0x10 | count;
			memcpy(&msg[1], tmp, count);
			snd_rawmidi_transmit_ack(substream, count);
			urb->transfer_buffer_length += count + 1;
			msg += count + 1;
			continue;
		}
		/* less than 9 bytes and no end byte - wait for more */
		if (count < MAX_AKAI_SYSEX_LEN) {
			ep->ports[0].active = 0;
			return;
		}
		/* 9 bytes and no end marker in sight - malformed, skip it */
		snd_rawmidi_transmit_ack(substream, count);
	}
}