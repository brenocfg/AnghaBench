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
struct vlan_rx_stats {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct sk_buff {int vlan_tci; int pkt_type; scalar_t__ len; int /*<<< orphan*/  priority; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_rx_stats; struct net_device* real_dev; } ;

/* Variables and functions */
#define  PACKET_BROADCAST 130 
 int PACKET_HOST ; 
#define  PACKET_MULTICAST 129 
#define  PACKET_OTHERHOST 128 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  netif_nit_deliver (struct sk_buff*) ; 
 struct vlan_rx_stats* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 TYPE_1__* vlan_dev_info (struct net_device*) ; 
 int /*<<< orphan*/  vlan_get_ingress_priority (struct net_device*,int) ; 

int vlan_hwaccel_do_receive(struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct vlan_rx_stats     *rx_stats;

	/*
	 * skb->dev will still be the base interface if the VLAN does
	 * not currently exist.  Do not continue if skb->dev is not a
	 * VLAN device.  Set pkt_type to PACKET_OTHERHOST for all VLANs
	 * except VID=0 since priority tagged frames are a special case.
	 * Mirrors what is done upstream in vlan_do_receive in kernel
	 * version 3.0 and later.
	*/
	if (!is_vlan_dev(skb->dev)) {
		if (skb->vlan_tci & VLAN_VID_MASK)
			skb->pkt_type = PACKET_OTHERHOST;
		return 0;
	}

	skb->dev = vlan_dev_info(dev)->real_dev;
	netif_nit_deliver(skb);

	skb->dev = dev;
	skb->priority = vlan_get_ingress_priority(dev, skb->vlan_tci);
	skb->vlan_tci = 0;

	rx_stats = per_cpu_ptr(vlan_dev_info(dev)->vlan_rx_stats,
			       smp_processor_id());

	rx_stats->rx_packets++;
	rx_stats->rx_bytes += skb->len;

	switch (skb->pkt_type) {
	case PACKET_BROADCAST:
		break;
	case PACKET_MULTICAST:
		rx_stats->multicast++;
		break;
	case PACKET_OTHERHOST:
		/* Our lower layer thinks this is not local, let's make sure.
		 * This allows the VLAN to have a different MAC than the
		 * underlying device, and still route correctly. */
		if (!compare_ether_addr(eth_hdr(skb)->h_dest,
					dev->dev_addr))
			skb->pkt_type = PACKET_HOST;
		break;
	};
	return 0;
}