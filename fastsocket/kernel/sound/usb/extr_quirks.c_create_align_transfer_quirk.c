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
struct usb_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct snd_usb_audio_quirk {int dummy; } ;
struct snd_usb_audio {int txfr_quirk; } ;

/* Variables and functions */

__attribute__((used)) static int create_align_transfer_quirk(struct snd_usb_audio *chip,
				       struct usb_interface *iface,
				       struct usb_driver *driver,
				       const struct snd_usb_audio_quirk *quirk)
{
	chip->txfr_quirk = 1;
	return 1;	/* Continue with creating streams and mixer */
}