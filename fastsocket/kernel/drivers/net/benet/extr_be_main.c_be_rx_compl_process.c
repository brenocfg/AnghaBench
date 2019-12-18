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
struct sk_buff {int /*<<< orphan*/  rxhash; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct net_device {int features; } ;
struct be_rx_obj {struct be_adapter* adapter; } ;
struct be_rx_compl_info {int /*<<< orphan*/  vlan_tag; scalar_t__ vlanf; int /*<<< orphan*/  rss_hash; } ;
struct be_adapter {int /*<<< orphan*/  vlan_grp; struct be_rx_obj* rx_obj; scalar_t__ rx_csum; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_drops_no_skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_RX_SKB_ALLOC_SIZE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  be_rx_compl_discard (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 scalar_t__ csum_passed (struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 TYPE_1__* rx_stats (struct be_rx_obj*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_fill_rx_data (struct be_rx_obj*,struct sk_buff*,struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_hwaccel_receive_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_rx_compl_process(struct be_rx_obj *rxo,
				struct be_rx_compl_info *rxcp)
{
	struct be_adapter *adapter = rxo->adapter;
	struct net_device *netdev = adapter->netdev;
	struct sk_buff *skb;

	skb = netdev_alloc_skb_ip_align(netdev, BE_RX_SKB_ALLOC_SIZE);
	if (unlikely(!skb)) {
		rx_stats(rxo)->rx_drops_no_skbs++;
		be_rx_compl_discard(rxo, rxcp);
		return;
	}

	skb_fill_rx_data(rxo, skb, rxcp);

	if (likely(adapter->rx_csum && csum_passed(rxcp)))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb_checksum_none_assert(skb);

	skb->protocol = eth_type_trans(skb, netdev);
	skb_record_rx_queue(skb, rxo - &adapter->rx_obj[0]);
	if (netdev->features & NETIF_F_RXHASH)
		skb->rxhash = rxcp->rss_hash;

	if (rxcp->vlanf)
		vlan_hwaccel_receive_skb(skb, adapter->vlan_grp,
					rxcp->vlan_tag);
	else
		netif_receive_skb(skb);
}