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
struct usb_serial {TYPE_1__* interface; } ;
struct TYPE_5__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_2__ desc; } ;
typedef  struct usb_endpoint_descriptor {int bEndpointAddress; } const usb_endpoint_descriptor ;
struct TYPE_6__ {struct usb_endpoint_descriptor const desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static struct usb_endpoint_descriptor const *find_ep(struct usb_serial const *serial,
						     int endpoint)
{
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *ep;
	int i;

	iface_desc = serial->interface->cur_altsetting;
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		ep = &iface_desc->endpoint[i].desc;
		if (ep->bEndpointAddress == endpoint)
			return ep;
	}
	dev_warn(&serial->interface->dev, "found no endpoint descriptor for "
		 "endpoint %x\n", endpoint);
	return NULL;
}