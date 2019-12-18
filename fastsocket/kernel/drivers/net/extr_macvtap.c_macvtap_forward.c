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
struct sk_buff {struct sk_buff* next; struct net_device* dev; } ;
struct net_device {scalar_t__ tx_queue_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_receive_queue; } ;
struct macvtap_queue {int flags; TYPE_1__ sk; } ;
struct macvlan_dev {unsigned long tap_features; } ;

/* Variables and functions */
 int IFF_VNET_HDR ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int POLLIN ; 
 int POLLRDBAND ; 
 int POLLRDNORM ; 
 unsigned long TAP_FEATURES ; 
 struct sk_buff* __skb_gso_segment (struct sk_buff*,unsigned long,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct macvtap_queue* macvtap_get_queue (struct net_device*,struct sk_buff*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_needs_gso (struct sk_buff*,unsigned long) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int macvtap_forward(struct net_device *dev, struct sk_buff *skb)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvtap_queue *q = macvtap_get_queue(dev, skb);
	unsigned long features = TAP_FEATURES;

	if (!q)
		goto drop;

	if (skb_queue_len(&q->sk.sk_receive_queue) >= dev->tx_queue_len)
		goto drop;

	skb->dev = dev;
	/* Apply the forward feature mask so that we perform segmentation
	 * according to users wishes.  This only works if VNET_HDR is
	 * enabled.
	 */
	if (q->flags & IFF_VNET_HDR)
		features |= vlan->tap_features;
	if (netif_needs_gso(skb, features)) {
		struct sk_buff *segs = __skb_gso_segment(skb, features, false);

		if (IS_ERR(segs))
			goto drop;

		if (!segs) {
			skb_queue_tail(&q->sk.sk_receive_queue, skb);
			goto wake_up;
		}

		kfree_skb(skb);
		while (segs) {
			struct sk_buff *nskb = segs->next;

			segs->next = NULL;
			skb_queue_tail(&q->sk.sk_receive_queue, segs);
			segs = nskb;
		}
	} else {
		skb_queue_tail(&q->sk.sk_receive_queue, skb);
	}

wake_up:
	wake_up_interruptible_poll(q->sk.sk_sleep, POLLIN | POLLRDNORM | POLLRDBAND);
	return NET_RX_SUCCESS;

drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}