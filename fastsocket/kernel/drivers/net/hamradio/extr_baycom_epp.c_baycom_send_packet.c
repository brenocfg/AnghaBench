#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {scalar_t__* data; int len; } ;
struct net_device {int dummy; } ;
struct baycom_state {struct sk_buff* skb; } ;

/* Variables and functions */
 int HDLCDRV_MAXFLEN ; 
 int NETDEV_TX_LOCKED ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  do_kiss_params (struct baycom_state*,scalar_t__*,int) ; 
 struct baycom_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int baycom_send_packet(struct sk_buff *skb, struct net_device *dev)
{
	struct baycom_state *bc = netdev_priv(dev);

	if (skb->data[0] != 0) {
		do_kiss_params(bc, skb->data, skb->len);
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	if (bc->skb)
		return NETDEV_TX_LOCKED;
	/* strip KISS byte */
	if (skb->len >= HDLCDRV_MAXFLEN+1 || skb->len < 3) {
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	netif_stop_queue(dev);
	bc->skb = skb;
	return NETDEV_TX_OK;
}