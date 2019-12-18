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
struct usbpn_dev {scalar_t__ tx_queue; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_pipe; int /*<<< orphan*/  usb; } ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {scalar_t__ tx_queue_len; TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PHONET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct usbpn_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_complete ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t usbpn_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct usbpn_dev *pnd = netdev_priv(dev);
	struct urb *req = NULL;
	unsigned long flags;
	int err;

	if (skb->protocol != htons(ETH_P_PHONET))
		goto drop;

	req = usb_alloc_urb(0, GFP_ATOMIC);
	if (!req)
		goto drop;
	usb_fill_bulk_urb(req, pnd->usb, pnd->tx_pipe, skb->data, skb->len,
				tx_complete, skb);
	req->transfer_flags = URB_ZERO_PACKET;
	err = usb_submit_urb(req, GFP_ATOMIC);
	if (err) {
		usb_free_urb(req);
		goto drop;
	}

	spin_lock_irqsave(&pnd->tx_lock, flags);
	pnd->tx_queue++;
	if (pnd->tx_queue >= dev->tx_queue_len)
		netif_stop_queue(dev);
	spin_unlock_irqrestore(&pnd->tx_lock, flags);
	return NETDEV_TX_OK;

drop:
	dev_kfree_skb(skb);
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}