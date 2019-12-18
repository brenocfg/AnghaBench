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
struct usb_interface {int dummy; } ;
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct gspca_dev {int /*<<< orphan*/  alt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  err (char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cit_get_packet_size(struct gspca_dev *gspca_dev)
{
	struct usb_host_interface *alt;
	struct usb_interface *intf;

	intf = usb_ifnum_to_if(gspca_dev->dev, gspca_dev->iface);
	alt = usb_altnum_to_altsetting(intf, gspca_dev->alt);
	if (!alt) {
		err("Couldn't get altsetting");
		return -EIO;
	}

	return le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
}