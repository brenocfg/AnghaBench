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
struct usb_mixer_interface {scalar_t__ urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int usb_submit_urb (scalar_t__,int /*<<< orphan*/ ) ; 

int snd_usb_mixer_activate(struct usb_mixer_interface *mixer)
{
	int err;

	if (mixer->urb) {
		err = usb_submit_urb(mixer->urb, GFP_NOIO);
		if (err < 0)
			return err;
	}

	return 0;
}