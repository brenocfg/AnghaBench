#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  usb; int /*<<< orphan*/  net; int /*<<< orphan*/  intr_interval; int /*<<< orphan*/  intr_buff; TYPE_5__* rx_skb; } ;
typedef  TYPE_1__ pegasus_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EthID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PEGASUS_MTU ; 
 int enable_net_traffic (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_skb_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  intr_callback ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_ifup (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_5__* pull_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  set_carrier (struct net_device*) ; 
 int set_registers (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pegasus_open(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);
	int res;

	if (pegasus->rx_skb == NULL)
		pegasus->rx_skb = pull_skb(pegasus);
	/*
	 ** Note: no point to free the pool.  it is empty :-)
	 */
	if (!pegasus->rx_skb)
		return -ENOMEM;

	res = set_registers(pegasus, EthID, 6, net->dev_addr);
	
	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU + 8,
			  read_bulk_callback, pegasus);
	if ((res = usb_submit_urb(pegasus->rx_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(pegasus->net);
		if (netif_msg_ifup(pegasus))
			pr_debug("%s: failed rx_urb, %d", net->name, res);
		goto exit;
	}

	usb_fill_int_urb(pegasus->intr_urb, pegasus->usb,
			 usb_rcvintpipe(pegasus->usb, 3),
			 pegasus->intr_buff, sizeof (pegasus->intr_buff),
			 intr_callback, pegasus, pegasus->intr_interval);
	if ((res = usb_submit_urb(pegasus->intr_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(pegasus->net);
		if (netif_msg_ifup(pegasus))
			pr_debug("%s: failed intr_urb, %d\n", net->name, res);
		usb_kill_urb(pegasus->rx_urb);
		goto exit;
	}
	if ((res = enable_net_traffic(net, pegasus->usb))) {
		if (netif_msg_ifup(pegasus))
			pr_debug("%s: can't enable_net_traffic() - %d\n",
					net->name, res);
		res = -EIO;
		usb_kill_urb(pegasus->rx_urb);
		usb_kill_urb(pegasus->intr_urb);
		free_skb_pool(pegasus);
		goto exit;
	}
	set_carrier(net);
	netif_start_queue(net);
	if (netif_msg_ifup(pegasus))
		pr_debug("%s: open\n", net->name);
	res = 0;
exit:
	return res;
}