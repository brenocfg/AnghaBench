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
struct usbpn_dev {struct urb** urbs; int /*<<< orphan*/  active_setting; int /*<<< orphan*/  usb; TYPE_3__* data_intf; } ;
struct urb {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {unsigned int bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usbpn_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ rx_submit (struct usbpn_dev*,struct urb*,int /*<<< orphan*/ ) ; 
 unsigned int rxq_size ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_set_interface (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbpn_close (struct net_device*) ; 

__attribute__((used)) static int usbpn_open(struct net_device *dev)
{
	struct usbpn_dev *pnd = netdev_priv(dev);
	int err;
	unsigned i;
	unsigned num = pnd->data_intf->cur_altsetting->desc.bInterfaceNumber;

	err = usb_set_interface(pnd->usb, num, pnd->active_setting);
	if (err)
		return err;

	for (i = 0; i < rxq_size; i++) {
		struct urb *req = usb_alloc_urb(0, GFP_KERNEL);

		if (!req || rx_submit(pnd, req, GFP_KERNEL)) {
			usbpn_close(dev);
			return -ENOMEM;
		}
		pnd->urbs[i] = req;
	}

	netif_wake_queue(dev);
	return 0;
}