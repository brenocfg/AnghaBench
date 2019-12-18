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
struct urb {unsigned int pipe; int transfer_flags; unsigned char* transfer_buffer; int transfer_buffer_length; int /*<<< orphan*/  interval; int /*<<< orphan*/  complete; struct hci_dev* context; int /*<<< orphan*/  dev; } ;
struct hci_dev {int /*<<< orphan*/  name; struct btusb_data* driver_data; } ;
struct btusb_data {int /*<<< orphan*/  isoc_anchor; TYPE_1__* isoc_rx_ep; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int BTUSB_MAX_ISOC_FRAMES ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,struct urb*,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int URB_FREE_BUFFER ; 
 int URB_ISO_ASAP ; 
 int /*<<< orphan*/  __fill_isoc_descriptor (struct urb*,int,int) ; 
 int /*<<< orphan*/  btusb_isoc_complete ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 unsigned int usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int btusb_submit_isoc_urb(struct hci_dev *hdev, gfp_t mem_flags)
{
	struct btusb_data *data = hdev->driver_data;
	struct urb *urb;
	unsigned char *buf;
	unsigned int pipe;
	int err, size;

	BT_DBG("%s", hdev->name);

	if (!data->isoc_rx_ep)
		return -ENODEV;

	urb = usb_alloc_urb(BTUSB_MAX_ISOC_FRAMES, mem_flags);
	if (!urb)
		return -ENOMEM;

	size = le16_to_cpu(data->isoc_rx_ep->wMaxPacketSize) *
						BTUSB_MAX_ISOC_FRAMES;

	buf = kmalloc(size, mem_flags);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	pipe = usb_rcvisocpipe(data->udev, data->isoc_rx_ep->bEndpointAddress);

	urb->dev      = data->udev;
	urb->pipe     = pipe;
	urb->context  = hdev;
	urb->complete = btusb_isoc_complete;
	urb->interval = data->isoc_rx_ep->bInterval;

	urb->transfer_flags  = URB_FREE_BUFFER | URB_ISO_ASAP;
	urb->transfer_buffer = buf;
	urb->transfer_buffer_length = size;

	__fill_isoc_descriptor(urb, size,
			le16_to_cpu(data->isoc_rx_ep->wMaxPacketSize));

	usb_anchor_urb(urb, &data->isoc_anchor);

	err = usb_submit_urb(urb, mem_flags);
	if (err < 0) {
		BT_ERR("%s urb %p submission failed (%d)",
						hdev->name, urb, -err);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}