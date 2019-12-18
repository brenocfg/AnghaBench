#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_wwan_intf_private {int /*<<< orphan*/  susp_lock; int /*<<< orphan*/  send_setup; } ;
struct usb_serial {struct usb_wwan_intf_private* private; TYPE_3__* interface; TYPE_5__* dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_9__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct TYPE_10__ {TYPE_4__ descriptor; } ;
struct TYPE_8__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_6__ {int bInterfaceClass; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ DLINK_PRODUCT_DWM_652 ; 
 scalar_t__ DLINK_VENDOR_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb_wwan_intf_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_send_setup ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int option_probe(struct usb_serial *serial,
			const struct usb_device_id *id)
{
	struct usb_wwan_intf_private *data;
	/* D-Link DWM 652 still exposes CD-Rom emulation interface in modem mode */
	if (serial->dev->descriptor.idVendor == DLINK_VENDOR_ID &&
		serial->dev->descriptor.idProduct == DLINK_PRODUCT_DWM_652 &&
		serial->interface->cur_altsetting->desc.bInterfaceClass == 0x8)
		return -ENODEV;

	data = serial->private = kzalloc(sizeof(struct usb_wwan_intf_private), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->send_setup = option_send_setup;
	spin_lock_init(&data->susp_lock);
	return 0;
}