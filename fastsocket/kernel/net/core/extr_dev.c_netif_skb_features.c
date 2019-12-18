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
struct vlan_ethhdr {scalar_t__ h_vlan_encapsulated_proto; } ;
struct sk_buff {scalar_t__ protocol; TYPE_3__* dev; scalar_t__ data; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_6__ {int features; int vlan_features; } ;
struct TYPE_5__ {scalar_t__ gso_max_segs; } ;
struct TYPE_4__ {scalar_t__ gso_segs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_GEN_CSUM ; 
 int NETIF_F_GSO_MASK ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_TX ; 
 int NETIF_F_SG ; 
 int harmonize_features (struct sk_buff*,scalar_t__,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_extended (TYPE_3__*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_tx_tag_present (struct sk_buff*) ; 

int netif_skb_features(struct sk_buff *skb)
{
	__be16 protocol = skb->protocol;
	int features = skb->dev->features;

	if (skb_shinfo(skb)->gso_segs > netdev_extended(skb->dev)->gso_max_segs)
		features &= ~NETIF_F_GSO_MASK;

	if (protocol == htons(ETH_P_8021Q)) {
		struct vlan_ethhdr *veh = (struct vlan_ethhdr *)skb->data;
		protocol = veh->h_vlan_encapsulated_proto;
	} else if (!vlan_tx_tag_present(skb)) {
		return harmonize_features(skb, protocol, features);
	}

	features &= (skb->dev->vlan_features | NETIF_F_HW_VLAN_TX);

	if (protocol != htons(ETH_P_8021Q)) {
		return harmonize_features(skb, protocol, features);
	} else {
		features &= NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_FRAGLIST |
				NETIF_F_GEN_CSUM | NETIF_F_HW_VLAN_TX;
		return harmonize_features(skb, protocol, features);
	}
}