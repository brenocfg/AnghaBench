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
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  in_frame; int /*<<< orphan*/ * head; int /*<<< orphan*/ * skb; } ;
struct kingsun_cb {int /*<<< orphan*/ * irlap; scalar_t__ receiving; TYPE_1__ rx_buff; int /*<<< orphan*/ * rx_urb; int /*<<< orphan*/ * tx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OUTSIDE_FRAME ; 
 int /*<<< orphan*/  irlap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 struct kingsun_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kingsun_net_close(struct net_device *netdev)
{
	struct kingsun_cb *kingsun = netdev_priv(netdev);

	/* Stop transmit processing */
	netif_stop_queue(netdev);

	/* Mop up receive && transmit urb's */
	usb_kill_urb(kingsun->tx_urb);
	usb_kill_urb(kingsun->rx_urb);

	usb_free_urb(kingsun->tx_urb);
	usb_free_urb(kingsun->rx_urb);

	kingsun->tx_urb = NULL;
	kingsun->rx_urb = NULL;

	kfree_skb(kingsun->rx_buff.skb);
	kingsun->rx_buff.skb = NULL;
	kingsun->rx_buff.head = NULL;
	kingsun->rx_buff.in_frame = FALSE;
	kingsun->rx_buff.state = OUTSIDE_FRAME;
	kingsun->receiving = 0;

	/* Stop and remove instance of IrLAP */
	if (kingsun->irlap)
		irlap_close(kingsun->irlap);

	kingsun->irlap = NULL;

	return 0;
}