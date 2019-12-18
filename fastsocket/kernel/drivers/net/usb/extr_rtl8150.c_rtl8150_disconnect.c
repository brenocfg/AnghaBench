#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  intr_buff; scalar_t__ rx_skb; int /*<<< orphan*/  tl; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8150_UNPLUG ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  free_all_urbs (TYPE_1__*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_skb_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_all_urbs (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8150_disconnect(struct usb_interface *intf)
{
	rtl8150_t *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (dev) {
		set_bit(RTL8150_UNPLUG, &dev->flags);
		tasklet_disable(&dev->tl);
		tasklet_kill(&dev->tl);
		unregister_netdev(dev->netdev);
		unlink_all_urbs(dev);
		free_all_urbs(dev);
		free_skb_pool(dev);
		if (dev->rx_skb)
			dev_kfree_skb(dev->rx_skb);
		kfree(dev->intr_buff);
		free_netdev(dev->netdev);
	}
}