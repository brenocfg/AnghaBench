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
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_host_endpoint {struct usb_endpoint_descriptor desc; } ;
struct usb_device {int dummy; } ;
struct stub_device {TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int USBIP_DIR_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct usb_host_endpoint* get_ep_from_epnum (struct usb_device*,int) ; 
 struct usb_device* interface_to_usbdev (TYPE_1__*) ; 
 scalar_t__ usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_xfer_control (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_xfer_int (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_xfer_isoc (struct usb_endpoint_descriptor*) ; 
 int usb_rcvbulkpipe (struct usb_device*,int) ; 
 int usb_rcvctrlpipe (struct usb_device*,int) ; 
 int usb_rcvintpipe (struct usb_device*,int) ; 
 int usb_rcvisocpipe (struct usb_device*,int) ; 
 int usb_sndbulkpipe (struct usb_device*,int) ; 
 int usb_sndctrlpipe (struct usb_device*,int) ; 
 int usb_sndintpipe (struct usb_device*,int) ; 
 int usb_sndisocpipe (struct usb_device*,int) ; 

__attribute__((used)) static int get_pipe(struct stub_device *sdev, int epnum, int dir)
{
	struct usb_device *udev = interface_to_usbdev(sdev->interface);
	struct usb_host_endpoint *ep;
	struct usb_endpoint_descriptor *epd = NULL;

	ep = get_ep_from_epnum(udev, epnum);
	if (!ep) {
		dev_err(&sdev->interface->dev, "no such endpoint?, %d\n",
			epnum);
		BUG();
	}

	epd = &ep->desc;


#if 0
	/* epnum 0 is always control */
	if (epnum == 0) {
		if (dir == USBIP_DIR_OUT)
			return usb_sndctrlpipe(udev, 0);
		else
			return usb_rcvctrlpipe(udev, 0);
	}
#endif

	if (usb_endpoint_xfer_control(epd)) {
		if (dir == USBIP_DIR_OUT)
			return usb_sndctrlpipe(udev, epnum);
		else
			return usb_rcvctrlpipe(udev, epnum);
	}

	if (usb_endpoint_xfer_bulk(epd)) {
		if (dir == USBIP_DIR_OUT)
			return usb_sndbulkpipe(udev, epnum);
		else
			return usb_rcvbulkpipe(udev, epnum);
	}

	if (usb_endpoint_xfer_int(epd)) {
		if (dir == USBIP_DIR_OUT)
			return usb_sndintpipe(udev, epnum);
		else
			return usb_rcvintpipe(udev, epnum);
	}

	if (usb_endpoint_xfer_isoc(epd)) {
		if (dir == USBIP_DIR_OUT)
			return usb_sndisocpipe(udev, epnum);
		else
			return usb_rcvisocpipe(udev, epnum);
	}

	/* NOT REACHED */
	dev_err(&sdev->interface->dev, "get pipe, epnum %d\n", epnum);
	return 0;
}