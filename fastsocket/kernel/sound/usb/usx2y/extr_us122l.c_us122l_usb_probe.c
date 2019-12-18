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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_register (struct snd_card*) ; 
 int /*<<< orphan*/  snd_card_set_dev (struct snd_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  us122l_create_card (struct snd_card*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ifnum_to_if (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usx2y_create_card (struct usb_device*,struct snd_card**) ; 

__attribute__((used)) static int us122l_usb_probe(struct usb_interface *intf,
			    const struct usb_device_id *device_id,
			    struct snd_card **cardp)
{
	struct usb_device *device = interface_to_usbdev(intf);
	struct snd_card *card;
	int err;

	err = usx2y_create_card(device, &card);
	if (err < 0)
		return err;

	snd_card_set_dev(card, &intf->dev);
	if (!us122l_create_card(card)) {
		snd_card_free(card);
		return -EINVAL;
	}

	err = snd_card_register(card);
	if (err < 0) {
		snd_card_free(card);
		return err;
	}

	usb_get_intf(usb_ifnum_to_if(device, 0));
	usb_get_dev(device);
	*cardp = card;
	return 0;
}