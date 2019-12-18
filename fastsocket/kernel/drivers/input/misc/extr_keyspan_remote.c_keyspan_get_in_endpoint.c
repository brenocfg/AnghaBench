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
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static struct usb_endpoint_descriptor *keyspan_get_in_endpoint(struct usb_host_interface *iface)
{

	struct usb_endpoint_descriptor *endpoint;
	int i;

	for (i = 0; i < iface->desc.bNumEndpoints; ++i) {
		endpoint = &iface->endpoint[i].desc;

		if (usb_endpoint_is_int_in(endpoint)) {
			/* we found our interrupt in endpoint */
			return endpoint;
		}
	}

	return NULL;
}