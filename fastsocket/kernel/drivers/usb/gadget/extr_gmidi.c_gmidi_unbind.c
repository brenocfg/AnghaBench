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
struct usb_gadget {int /*<<< orphan*/  ep0; } ;
struct snd_card {int dummy; } ;
struct gmidi_device {TYPE_1__* req; struct snd_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct gmidi_device*,char*) ; 
 int /*<<< orphan*/  USB_BUFSIZ ; 
 int /*<<< orphan*/  free_ep_req (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct gmidi_device* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  kfree (struct gmidi_device*) ; 
 int /*<<< orphan*/  set_gadget_data (struct usb_gadget*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

__attribute__((used)) static void /* __init_or_exit */ gmidi_unbind(struct usb_gadget *gadget)
{
	struct gmidi_device *dev = get_gadget_data(gadget);
	struct snd_card *card;

	DBG(dev, "unbind\n");

	card = dev->card;
	dev->card = NULL;
	if (card) {
		snd_card_free(card);
	}

	/* we've already been disconnected ... no i/o is active */
	if (dev->req) {
		dev->req->length = USB_BUFSIZ;
		free_ep_req(gadget->ep0, dev->req);
	}
	kfree(dev);
	set_gadget_data(gadget, NULL);
}