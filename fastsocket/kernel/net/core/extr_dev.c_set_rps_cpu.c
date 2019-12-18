#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {size_t rxhash; } ;
struct rps_dev_flow_table {size_t mask; struct rps_dev_flow* flows; } ;
struct rps_dev_flow {int filter; scalar_t__ cpu; int /*<<< orphan*/  last_qtail; } ;
struct netdev_rx_queue {int /*<<< orphan*/  rps_flow_table; } ;
struct netdev_rps_info {struct netdev_rx_queue* _rx; } ;
struct netdev_rfs_info {int (* ndo_rx_flow_steer ) (struct net_device*,struct sk_buff*,scalar_t__,size_t) ;int /*<<< orphan*/  rx_cpu_rmap; } ;
struct net_device {int features; } ;
struct TYPE_4__ {struct netdev_rfs_info rfs_data; struct netdev_rps_info rps_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  input_queue_head; } ;

/* Variables and functions */
 int NETIF_F_NTUPLE ; 
 scalar_t__ RPS_NO_CPU ; 
 int RPS_NO_FILTER ; 
 scalar_t__ cpu_rmap_lookup_index (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* netdev_extended (struct net_device*) ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,scalar_t__) ; 
 struct rps_dev_flow_table* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_get_rx_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_rx_queue_recorded (struct sk_buff*) ; 
 int /*<<< orphan*/  softnet_data ; 
 int stub1 (struct net_device*,struct sk_buff*,scalar_t__,size_t) ; 

__attribute__((used)) static struct rps_dev_flow *
set_rps_cpu(struct net_device *dev, struct sk_buff *skb,
	    struct rps_dev_flow *rflow, u16 next_cpu)
{
	if (next_cpu != RPS_NO_CPU) {
#ifdef CONFIG_RFS_ACCEL
		struct netdev_rx_queue *rxqueue;
		struct rps_dev_flow_table *flow_table;
		struct rps_dev_flow *old_rflow;
		struct netdev_rps_info *rpinfo = &netdev_extended(dev)->rps_data;
		struct netdev_rfs_info *rfinfo = &netdev_extended(dev)->rfs_data;
		u32 flow_id;
		u16 rxq_index;
		int rc;

		/* Should we steer this flow to a different hardware queue? */
		if (!skb_rx_queue_recorded(skb) || !rfinfo->rx_cpu_rmap ||
		    !(dev->features & NETIF_F_NTUPLE))
			goto out;
		rxq_index = cpu_rmap_lookup_index(rfinfo->rx_cpu_rmap, next_cpu);
		if (rxq_index == skb_get_rx_queue(skb))
			goto out;

		rxqueue = rpinfo->_rx + rxq_index;
		flow_table = rcu_dereference(rxqueue->rps_flow_table);
		if (!flow_table)
			goto out;
		flow_id = skb->rxhash & flow_table->mask;
		rc = rfinfo->ndo_rx_flow_steer(dev, skb, rxq_index, flow_id);
		if (rc < 0)
			goto out;
		old_rflow = rflow;
		rflow = &flow_table->flows[flow_id];
		rflow->filter = rc;
		if (old_rflow->filter == rflow->filter)
			old_rflow->filter = RPS_NO_FILTER;
	out:
#endif
		rflow->last_qtail =
			per_cpu(softnet_data, next_cpu).input_queue_head;
	}

	rflow->cpu = next_cpu;
	return rflow;
}