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
struct sk_buff {int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct netvsc_device {struct net_device* ndev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct hv_netvsc_packet {int /*<<< orphan*/  total_data_buflen; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  data; void* status; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 void* NVSP_STAT_FAIL ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int netvsc_recv_callback(struct hv_device *device_obj,
				struct hv_netvsc_packet *packet)
{
	struct net_device *net;
	struct sk_buff *skb;

	net = ((struct netvsc_device *)hv_get_drvdata(device_obj))->ndev;
	if (!net) {
		netdev_err(net, "got receive callback but net device"
			" not initialized yet\n");
		packet->status = NVSP_STAT_FAIL;
		return 0;
	}

	/* Allocate a skb - TODO direct I/O to pages? */
	skb = netdev_alloc_skb_ip_align(net, packet->total_data_buflen);
	if (unlikely(!skb)) {
		++net->stats.rx_dropped;
		packet->status = NVSP_STAT_FAIL;
		return 0;
	}

	/*
	 * Copy to skb. This copy is needed here since the memory pointed by
	 * hv_netvsc_packet cannot be deallocated
	 */
	memcpy(skb_put(skb, packet->total_data_buflen), packet->data,
		packet->total_data_buflen);

	skb->protocol = eth_type_trans(skb, net);
	skb->ip_summed = CHECKSUM_NONE;
	skb->vlan_tci = packet->vlan_tci;

	net->stats.rx_packets++;
	net->stats.rx_bytes += packet->total_data_buflen;

	/*
	 * Pass the skb back up. Network stack will deallocate the skb when it
	 * is done.
	 * TODO - use NAPI?
	 */
	netif_rx(skb);

	return 0;
}