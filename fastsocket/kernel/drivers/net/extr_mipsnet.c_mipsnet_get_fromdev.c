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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {size_t rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 size_t EFAULT ; 
 size_t ENOMEM ; 
 scalar_t__ NET_IP_ALIGN ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ ioiocpy_frommipsnet (struct net_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static inline ssize_t mipsnet_get_fromdev(struct net_device *dev, size_t len)
{
	struct sk_buff *skb;

	if (!len)
		return len;

	skb = dev_alloc_skb(len + NET_IP_ALIGN);
	if (!skb) {
		dev->stats.rx_dropped++;
		return -ENOMEM;
	}

	skb_reserve(skb, NET_IP_ALIGN);
	if (ioiocpy_frommipsnet(dev, skb_put(skb, len), len))
		return -EFAULT;

	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	netif_rx(skb);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	return len;
}