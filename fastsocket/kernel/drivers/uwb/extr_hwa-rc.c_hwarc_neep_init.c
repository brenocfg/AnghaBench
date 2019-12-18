#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uwb_rc {struct hwarc* priv; } ;
struct device {int dummy; } ;
struct usb_interface {TYPE_2__* cur_altsetting; struct device dev; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int dummy; } ;
struct hwarc {int /*<<< orphan*/ * rd_buffer; int /*<<< orphan*/ * neep_urb; struct usb_interface* usb_iface; } ;
struct TYPE_4__ {TYPE_1__* endpoint; } ;
struct TYPE_3__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  hwarc_neep_cb ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ *,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hwarc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwarc_neep_init(struct uwb_rc *rc)
{
	struct hwarc *hwarc = rc->priv;
	struct usb_interface *iface = hwarc->usb_iface;
	struct usb_device *usb_dev = interface_to_usbdev(iface);
	struct device *dev = &iface->dev;
	int result;
	struct usb_endpoint_descriptor *epd;

	epd = &iface->cur_altsetting->endpoint[0].desc;
	hwarc->rd_buffer = (void *) __get_free_page(GFP_KERNEL);
	if (hwarc->rd_buffer == NULL) {
		dev_err(dev, "Unable to allocate notification's read buffer\n");
		goto error_rd_buffer;
	}
	hwarc->neep_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (hwarc->neep_urb == NULL) {
		dev_err(dev, "Unable to allocate notification URB\n");
		goto error_urb_alloc;
	}
	usb_fill_int_urb(hwarc->neep_urb, usb_dev,
			 usb_rcvintpipe(usb_dev, epd->bEndpointAddress),
			 hwarc->rd_buffer, PAGE_SIZE,
			 hwarc_neep_cb, hwarc, epd->bInterval);
	result = usb_submit_urb(hwarc->neep_urb, GFP_ATOMIC);
	if (result < 0) {
		dev_err(dev, "Cannot submit notification URB: %d\n", result);
		goto error_neep_submit;
	}
	return 0;

error_neep_submit:
	usb_free_urb(hwarc->neep_urb);
error_urb_alloc:
	free_page((unsigned long)hwarc->rd_buffer);
error_rd_buffer:
	return -ENOMEM;
}