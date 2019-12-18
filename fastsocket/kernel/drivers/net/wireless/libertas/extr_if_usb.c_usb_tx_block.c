#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct if_usb_card {TYPE_2__* udev; TYPE_1__* tx_urb; int /*<<< orphan*/  ep_out; scalar_t__ surprise_removed; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  if_usb_write_bulk_callback ; 
 int /*<<< orphan*/  lbs_deb_usb2 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lbs_deb_usbd (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct if_usb_card*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_tx_block(struct if_usb_card *cardp, uint8_t *payload, uint16_t nb)
{
	int ret = -1;

	/* check if device is removed */
	if (cardp->surprise_removed) {
		lbs_deb_usbd(&cardp->udev->dev, "Device removed\n");
		goto tx_ret;
	}

	usb_fill_bulk_urb(cardp->tx_urb, cardp->udev,
			  usb_sndbulkpipe(cardp->udev,
					  cardp->ep_out),
			  payload, nb, if_usb_write_bulk_callback, cardp);

	cardp->tx_urb->transfer_flags |= URB_ZERO_PACKET;

	if ((ret = usb_submit_urb(cardp->tx_urb, GFP_ATOMIC))) {
		lbs_deb_usbd(&cardp->udev->dev, "usb_submit_urb failed: %d\n", ret);
		ret = -1;
	} else {
		lbs_deb_usb2(&cardp->udev->dev, "usb_submit_urb success\n");
		ret = 0;
	}

tx_ret:
	return ret;
}