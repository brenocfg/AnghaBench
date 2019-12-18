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
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int num_tx_rings_p_up; } ;

/* Variables and functions */
 int VLAN_PRIO_SHIFT ; 
 int __skb_tx_hash (struct net_device*,struct sk_buff*,int) ; 
 scalar_t__ netdev_get_num_tc (struct net_device*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int skb_tx_hash (struct net_device*,struct sk_buff*) ; 
 int vlan_tx_tag_get (struct sk_buff*) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

u16 mlx4_en_select_queue(struct net_device *dev, struct sk_buff *skb)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	u16 rings_p_up = priv->num_tx_rings_p_up;
	u8 up = 0;

	if (netdev_get_num_tc(dev))
		return skb_tx_hash(dev, skb);

	if (vlan_tx_tag_present(skb))
		up = vlan_tx_tag_get(skb) >> VLAN_PRIO_SHIFT;

	return __skb_tx_hash(dev, skb, rings_p_up) + up * rings_p_up;
}