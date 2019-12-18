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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; } ;
struct netdev_queue {unsigned int tx_bytes; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  real_dev; int /*<<< orphan*/  vlan_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NET_XMIT_SUCCESS ; 
 struct sk_buff* __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_dev_get_egress_qos_mask (struct net_device*,struct sk_buff*) ; 
 TYPE_1__* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t vlan_dev_hwaccel_hard_start_xmit(struct sk_buff *skb,
						    struct net_device *dev)
{
	int i = skb_get_queue_mapping(skb);
	struct netdev_queue *txq = netdev_get_tx_queue(dev, i);
	u16 vlan_tci;
	unsigned int len;
	int ret;

	vlan_tci = vlan_dev_info(dev)->vlan_id;
	vlan_tci |= vlan_dev_get_egress_qos_mask(dev, skb);
	skb = __vlan_hwaccel_put_tag(skb, vlan_tci);

	skb->dev = vlan_dev_info(dev)->real_dev;
	len = skb->len;
	ret = dev_queue_xmit(skb);

	if (likely(ret == NET_XMIT_SUCCESS)) {
		txq->tx_packets++;
		txq->tx_bytes += len;
	} else
		txq->tx_dropped++;

	return NETDEV_TX_OK;
}