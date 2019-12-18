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
struct snd_usb_midi_out_endpoint {TYPE_1__* ports; scalar_t__ max_transfer; } ;
struct TYPE_2__ {scalar_t__ active; int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,int*,scalar_t__) ; 

__attribute__((used)) static void snd_usbmidi_novation_output(struct snd_usb_midi_out_endpoint* ep,
					struct urb *urb)
{
	uint8_t* transfer_buffer;
	int count;

	if (!ep->ports[0].active)
		return;
	transfer_buffer = urb->transfer_buffer;
	count = snd_rawmidi_transmit(ep->ports[0].substream,
				     &transfer_buffer[2],
				     ep->max_transfer - 2);
	if (count < 1) {
		ep->ports[0].active = 0;
		return;
	}
	transfer_buffer[0] = 0;
	transfer_buffer[1] = count;
	urb->transfer_buffer_length = 2 + count;
}