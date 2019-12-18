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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  needed_headroom; } ;
struct TYPE_4__ {int o_flags; int /*<<< orphan*/  iph; } ;
struct ip_tunnel {TYPE_2__ parms; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TUNNEL_CSUM ; 
 int /*<<< orphan*/  __gre_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* gre_handle_offloads (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t gre_tap_xmit(struct sk_buff *skb,
				struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);

	skb = gre_handle_offloads(skb, !!(tunnel->parms.o_flags&TUNNEL_CSUM));
	if (IS_ERR(skb))
		goto out;

	if (skb_cow_head(skb, dev->needed_headroom))
		goto free_skb;

	__gre_xmit(skb, dev, &tunnel->parms.iph, htons(ETH_P_TEB));

	return NETDEV_TX_OK;

free_skb:
	dev_kfree_skb(skb);
out:
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}