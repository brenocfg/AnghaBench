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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {struct usb_interface* interface; struct usb_device* dev; } ;
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct usb_endpoint_descriptor {scalar_t__ wMaxPacketSize; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct ftdi_private {scalar_t__ max_packet_size; } ;
struct TYPE_4__ {unsigned int bNumEndpoints; } ;
struct TYPE_6__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void ftdi_set_max_packet_size(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_serial *serial = port->serial;
	struct usb_device *udev = serial->dev;

	struct usb_interface *interface = serial->interface;
	struct usb_endpoint_descriptor *ep_desc = &interface->cur_altsetting->endpoint[1].desc;

	unsigned num_endpoints;
	int i = 0;

	num_endpoints = interface->cur_altsetting->desc.bNumEndpoints;
	dev_info(&udev->dev, "Number of endpoints %d\n", num_endpoints);

	/* NOTE: some customers have programmed FT232R/FT245R devices
	 * with an endpoint size of 0 - not good.  In this case, we
	 * want to override the endpoint descriptor setting and use a
	 * value of 64 for wMaxPacketSize */
	for (i = 0; i < num_endpoints; i++) {
		dev_info(&udev->dev, "Endpoint %d MaxPacketSize %d\n", i+1,
			interface->cur_altsetting->endpoint[i].desc.wMaxPacketSize);
		ep_desc = &interface->cur_altsetting->endpoint[i].desc;
		if (ep_desc->wMaxPacketSize == 0) {
			ep_desc->wMaxPacketSize = cpu_to_le16(0x40);
			dev_info(&udev->dev, "Overriding wMaxPacketSize on endpoint %d\n", i);
		}
	}

	/* set max packet size based on descriptor */
	priv->max_packet_size = ep_desc->wMaxPacketSize;

	dev_info(&udev->dev, "Setting MaxPacketSize %d\n", priv->max_packet_size);
}