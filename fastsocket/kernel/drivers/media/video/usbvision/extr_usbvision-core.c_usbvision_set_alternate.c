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
struct usb_usbvision {int iface_alt; int num_alt; scalar_t__* alt_max_pkt_size; scalar_t__ isoc_packet_size; TYPE_1__* dev; int /*<<< orphan*/  iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC ; 
 int /*<<< orphan*/  DBG_ISOC ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,int) ; 
 int usb_set_interface (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

int usbvision_set_alternate(struct usb_usbvision *dev)
{
	int err_code, prev_alt = dev->iface_alt;
	int i;

	dev->iface_alt = 0;
	for (i = 0; i < dev->num_alt; i++)
		if (dev->alt_max_pkt_size[i] > dev->alt_max_pkt_size[dev->iface_alt])
			dev->iface_alt = i;

	if (dev->iface_alt != prev_alt) {
		dev->isoc_packet_size = dev->alt_max_pkt_size[dev->iface_alt];
		PDEBUG(DBG_FUNC, "setting alternate %d with max_packet_size=%u",
				dev->iface_alt, dev->isoc_packet_size);
		err_code = usb_set_interface(dev->dev, dev->iface, dev->iface_alt);
		if (err_code < 0) {
			dev_err(&dev->dev->dev,
				"cannot change alternate number to %d (error=%i)\n",
					dev->iface_alt, err_code);
			return err_code;
		}
	}

	PDEBUG(DBG_ISOC, "ISO Packet Length:%d", dev->isoc_packet_size);

	return 0;
}