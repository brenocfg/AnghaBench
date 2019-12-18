#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  tl; int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; int /*<<< orphan*/  rx_urb; struct sk_buff* rx_skb; int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_pool_lock; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTL8150_MTU ; 
 int /*<<< orphan*/  RX_URB_FAIL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_skb_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 struct sk_buff* pull_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_fixup(unsigned long data)
{
	rtl8150_t *dev;
	struct sk_buff *skb;
	int status;

	dev = (rtl8150_t *)data;

	spin_lock_irq(&dev->rx_pool_lock);
	fill_skb_pool(dev);
	spin_unlock_irq(&dev->rx_pool_lock);
	if (test_bit(RX_URB_FAIL, &dev->flags))
		if (dev->rx_skb)
			goto try_again;
	spin_lock_irq(&dev->rx_pool_lock);
	skb = pull_skb(dev);
	spin_unlock_irq(&dev->rx_pool_lock);
	if (skb == NULL)
		goto tlsched;
	dev->rx_skb = skb;
	usb_fill_bulk_urb(dev->rx_urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
		      dev->rx_skb->data, RTL8150_MTU, read_bulk_callback, dev);
try_again:
	status = usb_submit_urb(dev->rx_urb, GFP_ATOMIC);
	if (status == -ENODEV) {
		netif_device_detach(dev->netdev);
	} else if (status) {
		set_bit(RX_URB_FAIL, &dev->flags);
		goto tlsched;
	} else {
		clear_bit(RX_URB_FAIL, &dev->flags);
	}

	return;
tlsched:
	tasklet_schedule(&dev->tl);
}