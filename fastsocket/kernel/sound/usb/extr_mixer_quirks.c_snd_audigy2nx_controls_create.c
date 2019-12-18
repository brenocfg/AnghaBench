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
struct usb_mixer_interface {int* audigy2nx_leds; TYPE_1__* chip; } ;
struct TYPE_2__ {scalar_t__ usb_id; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_ID (int,int) ; 
 int /*<<< orphan*/ * snd_audigy2nx_controls ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct usb_mixer_interface*) ; 

__attribute__((used)) static int snd_audigy2nx_controls_create(struct usb_mixer_interface *mixer)
{
	int i, err;

	for (i = 0; i < ARRAY_SIZE(snd_audigy2nx_controls); ++i) {
		/* USB X-Fi S51 doesn't have a CMSS LED */
		if ((mixer->chip->usb_id == USB_ID(0x041e, 0x3042)) && i == 0)
			continue;
		/* USB X-Fi S51 Pro doesn't have one either */
		if ((mixer->chip->usb_id == USB_ID(0x041e, 0x30df)) && i == 0)
			continue;
		if (i > 1 && /* Live24ext has 2 LEDs only */
			(mixer->chip->usb_id == USB_ID(0x041e, 0x3040) ||
			 mixer->chip->usb_id == USB_ID(0x041e, 0x3042) ||
			 mixer->chip->usb_id == USB_ID(0x041e, 0x30df) ||
			 mixer->chip->usb_id == USB_ID(0x041e, 0x3048)))
			break; 
		err = snd_ctl_add(mixer->chip->card,
				  snd_ctl_new1(&snd_audigy2nx_controls[i], mixer));
		if (err < 0)
			return err;
	}
	mixer->audigy2nx_leds[1] = 1; /* Power LED is on by default */
	return 0;
}