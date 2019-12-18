#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  name; struct btusb_data* driver_data; } ;
struct btusb_data {int isoc_altsetting; struct usb_endpoint_descriptor* isoc_rx_ep; struct usb_endpoint_descriptor* isoc_tx_ep; int /*<<< orphan*/  udev; struct usb_interface* isoc; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct TYPE_6__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,...) ; 
 int ENODEV ; 
 scalar_t__ usb_endpoint_is_isoc_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_isoc_out (struct usb_endpoint_descriptor*) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int inline __set_isoc_interface(struct hci_dev *hdev, int altsetting)
{
	struct btusb_data *data = hdev->driver_data;
	struct usb_interface *intf = data->isoc;
	struct usb_endpoint_descriptor *ep_desc;
	int i, err;

	if (!data->isoc)
		return -ENODEV;

	err = usb_set_interface(data->udev, 1, altsetting);
	if (err < 0) {
		BT_ERR("%s setting interface failed (%d)", hdev->name, -err);
		return err;
	}

	data->isoc_altsetting = altsetting;

	data->isoc_tx_ep = NULL;
	data->isoc_rx_ep = NULL;

	for (i = 0; i < intf->cur_altsetting->desc.bNumEndpoints; i++) {
		ep_desc = &intf->cur_altsetting->endpoint[i].desc;

		if (!data->isoc_tx_ep && usb_endpoint_is_isoc_out(ep_desc)) {
			data->isoc_tx_ep = ep_desc;
			continue;
		}

		if (!data->isoc_rx_ep && usb_endpoint_is_isoc_in(ep_desc)) {
			data->isoc_rx_ep = ep_desc;
			continue;
		}
	}

	if (!data->isoc_tx_ep || !data->isoc_rx_ep) {
		BT_ERR("%s invalid SCO descriptors", hdev->name);
		return -ENODEV;
	}

	return 0;
}