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
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  netdev; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  intr_interval; int /*<<< orphan*/  intr_buff; int /*<<< orphan*/  udev; TYPE_5__* rx_skb; } ;
typedef  TYPE_1__ rtl8150_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  INTBUFSIZE ; 
 int /*<<< orphan*/  RTL8150_MTU ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  enable_net_traffic (TYPE_1__*) ; 
 int /*<<< orphan*/  intr_callback ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 TYPE_5__* pull_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  set_carrier (struct net_device*) ; 
 int /*<<< orphan*/  set_registers (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8150_open(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	int res;

	if (dev->rx_skb == NULL)
		dev->rx_skb = pull_skb(dev);
	if (!dev->rx_skb)
		return -ENOMEM;

	set_registers(dev, IDR, 6, netdev->dev_addr);
	
	usb_fill_bulk_urb(dev->rx_urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
		      dev->rx_skb->data, RTL8150_MTU, read_bulk_callback, dev);
	if ((res = usb_submit_urb(dev->rx_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_warn(&netdev->dev, "rx_urb submit failed: %d\n", res);
		return res;
	}
	usb_fill_int_urb(dev->intr_urb, dev->udev, usb_rcvintpipe(dev->udev, 3),
		     dev->intr_buff, INTBUFSIZE, intr_callback,
		     dev, dev->intr_interval);
	if ((res = usb_submit_urb(dev->intr_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_warn(&netdev->dev, "intr_urb submit failed: %d\n", res);
		usb_kill_urb(dev->rx_urb);
		return res;
	}
	enable_net_traffic(dev);
	set_carrier(netdev);
	netif_start_queue(netdev);

	return res;
}