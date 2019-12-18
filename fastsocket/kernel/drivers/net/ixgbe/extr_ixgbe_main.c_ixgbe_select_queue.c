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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int real_num_tx_queues; } ;
struct ixgbe_ring_feature {int indices; scalar_t__ offset; } ;
struct ixgbe_adapter {int flags; struct ixgbe_ring_feature* ring_feature; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_FCOE ; 
 int /*<<< orphan*/  ETH_P_FIP ; 
 int IXGBE_FLAG_FCOE_ENABLED ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 size_t RING_F_FCOE ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 
 int skb_tx_hash (struct net_device*,struct sk_buff*) ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static u16 ixgbe_select_queue(struct net_device *dev, struct sk_buff *skb)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	int txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) :
					       smp_processor_id();
#ifdef IXGBE_FCOE
	__be16 protocol = vlan_get_protocol(skb);

	if (((protocol == htons(ETH_P_FCOE)) ||
	    (protocol == htons(ETH_P_FIP))) &&
	    (adapter->flags & IXGBE_FLAG_FCOE_ENABLED)) {
		struct ixgbe_ring_feature *f;

		f = &adapter->ring_feature[RING_F_FCOE];

		while (txq >= f->indices)
			txq -= f->indices;
		txq += adapter->ring_feature[RING_F_FCOE].offset;

		return txq;
	}
#endif

	if (adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE) {
		while (unlikely(txq >= dev->real_num_tx_queues))
			txq -= dev->real_num_tx_queues;
		return txq;
	}

	return skb_tx_hash(dev, skb);
}