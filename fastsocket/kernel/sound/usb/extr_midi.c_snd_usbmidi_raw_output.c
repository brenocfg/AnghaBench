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
struct urb {int transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;
struct snd_usb_midi_out_endpoint {TYPE_1__* ports; int /*<<< orphan*/  max_transfer; } ;
struct TYPE_2__ {scalar_t__ active; int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_usbmidi_raw_output(struct snd_usb_midi_out_endpoint* ep,
				   struct urb *urb)
{
	int count;

	if (!ep->ports[0].active)
		return;
	count = snd_rawmidi_transmit(ep->ports[0].substream,
				     urb->transfer_buffer,
				     ep->max_transfer);
	if (count < 1) {
		ep->ports[0].active = 0;
		return;
	}
	urb->transfer_buffer_length = count;
}