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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  skb; } ;
struct mcs_cb {int /*<<< orphan*/ * irlap; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  rx_urb; TYPE_1__ rx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  irlap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct mcs_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcs_net_close(struct net_device *netdev)
{
	int ret = 0;
	struct mcs_cb *mcs = netdev_priv(netdev);

	/* Stop transmit processing */
	netif_stop_queue(netdev);

	kfree_skb(mcs->rx_buff.skb);

	/* kill and free the receive and transmit URBs */
	usb_kill_urb(mcs->rx_urb);
	usb_free_urb(mcs->rx_urb);
	usb_kill_urb(mcs->tx_urb);
	usb_free_urb(mcs->tx_urb);

	/* Stop and remove instance of IrLAP */
	if (mcs->irlap)
		irlap_close(mcs->irlap);

	mcs->irlap = NULL;
	return ret;
}