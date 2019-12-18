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
struct usb_serial {TYPE_1__* dev; } ;
struct usb_endpoint_descriptor {scalar_t__ wMaxPacketSize; } ;
struct usb_host_endpoint {scalar_t__ enabled; struct usb_endpoint_descriptor desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct usb_host_endpoint** ep_in; } ;

/* Variables and functions */
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ftdi_mtxorb_hack_setup(struct usb_serial *serial)
{
	struct usb_host_endpoint *ep = serial->dev->ep_in[1];
	struct usb_endpoint_descriptor *ep_desc = &ep->desc;

	if (ep->enabled && ep_desc->wMaxPacketSize == 0) {
		ep_desc->wMaxPacketSize = cpu_to_le16(0x40);
		dev_info(&serial->dev->dev,
			 "Fixing invalid wMaxPacketSize on read pipe\n");
	}

	return 0;
}