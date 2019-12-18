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
struct usb_interface_cache {struct usb_host_interface* altsetting; } ;
struct usb_interface {int dummy; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 char* usb_dump_endpoint_descriptor (int,char*,char*,int /*<<< orphan*/ *) ; 
 char* usb_dump_interface_descriptor (char*,char*,struct usb_interface_cache const*,struct usb_interface const*,int) ; 

__attribute__((used)) static char *usb_dump_interface(int speed, char *start, char *end,
				const struct usb_interface_cache *intfc,
				const struct usb_interface *iface, int setno)
{
	const struct usb_host_interface *desc = &intfc->altsetting[setno];
	int i;

	start = usb_dump_interface_descriptor(start, end, intfc, iface, setno);
	for (i = 0; i < desc->desc.bNumEndpoints; i++) {
		if (start > end)
			return start;
		start = usb_dump_endpoint_descriptor(speed,
				start, end, &desc->endpoint[i].desc);
	}
	return start;
}