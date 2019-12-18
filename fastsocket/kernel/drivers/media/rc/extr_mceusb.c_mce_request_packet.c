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
typedef  int /*<<< orphan*/  usb_complete_t ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct urb {int transfer_buffer_length; int /*<<< orphan*/  dev; } ;
struct mceusb_dev {int /*<<< orphan*/  usbdev; int /*<<< orphan*/  send_flags; struct urb* urb_in; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MCEUSB_RX ; 
 int MCEUSB_TX ; 
 int /*<<< orphan*/  RECV_FLAG_IN_PROGRESS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mce_async_callback ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,struct mceusb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_request_packet(struct mceusb_dev *ir,
			       struct usb_endpoint_descriptor *ep,
			       unsigned char *data, int size, int urb_type)
{
	int res;
	struct urb *async_urb;
	struct device *dev = ir->dev;
	unsigned char *async_buf;

	if (urb_type == MCEUSB_TX) {
		async_urb = usb_alloc_urb(0, GFP_KERNEL);
		if (unlikely(!async_urb)) {
			dev_err(dev, "Error, couldn't allocate urb!\n");
			return;
		}

		async_buf = kzalloc(size, GFP_KERNEL);
		if (!async_buf) {
			dev_err(dev, "Error, couldn't allocate buf!\n");
			usb_free_urb(async_urb);
			return;
		}

		/* outbound data */
		usb_fill_int_urb(async_urb, ir->usbdev,
			usb_sndintpipe(ir->usbdev, ep->bEndpointAddress),
			async_buf, size, (usb_complete_t)mce_async_callback,
			ir, ep->bInterval);
		memcpy(async_buf, data, size);

	} else if (urb_type == MCEUSB_RX) {
		/* standard request */
		async_urb = ir->urb_in;
		ir->send_flags = RECV_FLAG_IN_PROGRESS;

	} else {
		dev_err(dev, "Error! Unknown urb type %d\n", urb_type);
		return;
	}

	dev_dbg(dev, "receive request called (size=%#x)\n", size);

	async_urb->transfer_buffer_length = size;
	async_urb->dev = ir->usbdev;

	res = usb_submit_urb(async_urb, GFP_ATOMIC);
	if (res) {
		dev_dbg(dev, "receive request FAILED! (res=%d)\n", res);
		return;
	}
	dev_dbg(dev, "receive request complete (res=%d)\n", res);
}