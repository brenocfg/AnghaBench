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
struct usb_mixer_interface {struct usb_mixer_interface* rc_setup_packet; TYPE_1__* rc_urb; TYPE_1__* urb; struct usb_mixer_interface* id_elems; } ;
struct TYPE_2__ {struct usb_mixer_interface* transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_mixer_interface*) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static void snd_usb_mixer_free(struct usb_mixer_interface *mixer)
{
	kfree(mixer->id_elems);
	if (mixer->urb) {
		kfree(mixer->urb->transfer_buffer);
		usb_free_urb(mixer->urb);
	}
	usb_free_urb(mixer->rc_urb);
	kfree(mixer->rc_setup_packet);
	kfree(mixer);
}