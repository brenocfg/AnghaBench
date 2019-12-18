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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct mpoa_client {int number_of_mps_macs; TYPE_1__* old_ops; scalar_t__ mps_macs; } ;
struct iphdr {int dummy; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int ihl; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ndo_start_xmit ) (struct sk_buff*,struct net_device*) ;} ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  compare_ether_addr (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mpoa_client* find_mpc_by_lec (struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ send_via_shortcut (struct sk_buff*,struct mpoa_client*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t mpc_send_packet(struct sk_buff *skb,
					 struct net_device *dev)
{
	struct mpoa_client *mpc;
	struct ethhdr *eth;
	int i = 0;

	mpc = find_mpc_by_lec(dev); /* this should NEVER fail */
	if(mpc == NULL) {
		printk("mpoa: (%s) mpc_send_packet: no MPC found\n", dev->name);
		goto non_ip;
	}

	eth = (struct ethhdr *)skb->data;
	if (eth->h_proto != htons(ETH_P_IP))
		goto non_ip; /* Multi-Protocol Over ATM :-) */

	/* Weed out funny packets (e.g., AF_PACKET or raw). */
	if (skb->len < ETH_HLEN + sizeof(struct iphdr))
		goto non_ip;
	skb_set_network_header(skb, ETH_HLEN);
	if (skb->len < ETH_HLEN + ip_hdr(skb)->ihl * 4 || ip_hdr(skb)->ihl < 5)
		goto non_ip;

	while (i < mpc->number_of_mps_macs) {
		if (!compare_ether_addr(eth->h_dest, (mpc->mps_macs + i*ETH_ALEN)))
			if ( send_via_shortcut(skb, mpc) == 0 )           /* try shortcut */
				return NETDEV_TX_OK;                      /* success!     */
		i++;
	}

 non_ip:
	return mpc->old_ops->ndo_start_xmit(skb,dev);
}