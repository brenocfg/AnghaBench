#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct sk_buff {unsigned int protocol; TYPE_2__* sk; int /*<<< orphan*/  priority; } ;
struct netdev_qos_info {TYPE_1__* tc_to_txq; scalar_t__ num_tc; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {struct netdev_qos_info qos_data; } ;
struct TYPE_5__ {unsigned int sk_hash; } ;
struct TYPE_4__ {unsigned int offset; unsigned int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashrnd ; 
 unsigned int jhash_1word (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_extended (struct net_device const*) ; 
 size_t netdev_get_prio_tc_map (struct net_device const*,int /*<<< orphan*/ ) ; 
 unsigned int skb_get_rx_queue (struct sk_buff const*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff const*) ; 
 scalar_t__ unlikely (int) ; 

u16 __skb_tx_hash(const struct net_device *dev, const struct sk_buff *skb,
		  unsigned int num_tx_queues)
{
	struct netdev_qos_info *qos = &netdev_extended(dev)->qos_data;
	u32 hash;
	u16 qoffset = 0;
	u16 qcount = num_tx_queues;

	if (skb_rx_queue_recorded(skb)) {
		hash = skb_get_rx_queue(skb);
		while (unlikely(hash >= num_tx_queues))
			hash -= num_tx_queues;
		return hash;
	}

	if (qos->num_tc) {
		u8 tc = netdev_get_prio_tc_map(dev, skb->priority);
		qoffset = qos->tc_to_txq[tc].offset;
		qcount = qos->tc_to_txq[tc].count;
	}

	if (skb->sk && skb->sk->sk_hash)
		hash = skb->sk->sk_hash;
	else
		hash = skb->protocol;

	hash = jhash_1word(hash, hashrnd);

	return (u16) (((u64) hash * qcount) >> 32) + qoffset;
}