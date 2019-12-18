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
struct urb {scalar_t__ status; struct snd_usb_caiaqdev* context; } ;
struct snd_usb_caiaqdev {int /*<<< orphan*/  midi_out_substream; scalar_t__ midi_out_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usb_caiaq_midi_send (struct snd_usb_caiaqdev*,int /*<<< orphan*/ ) ; 

void snd_usb_caiaq_midi_output_done(struct urb* urb)
{
	struct snd_usb_caiaqdev *dev = urb->context;

	dev->midi_out_active = 0;
	if (urb->status != 0)
		return;

	if (!dev->midi_out_substream)
		return;

	snd_usb_caiaq_midi_send(dev, dev->midi_out_substream);
}