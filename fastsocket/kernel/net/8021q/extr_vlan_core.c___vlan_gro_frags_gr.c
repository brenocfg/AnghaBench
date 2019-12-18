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
struct vlan_group {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct napi_struct {int dummy; } ;
typedef  int /*<<< orphan*/  gro_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRO_DROP ; 
 int /*<<< orphan*/  GRO_NORMAL ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_frags_finish (struct napi_struct*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_frags_skb (struct napi_struct*) ; 
 scalar_t__ netpoll_rx_on (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_gro_common (struct napi_struct*,struct vlan_group*,unsigned int,struct sk_buff*) ; 
 scalar_t__ vlan_hwaccel_receive_skb (struct sk_buff*,struct vlan_group*,unsigned int) ; 

__attribute__((used)) static inline gro_result_t __vlan_gro_frags_gr(struct napi_struct *napi,
					       struct vlan_group *grp,
					       unsigned int vlan_tci)
{
	struct sk_buff *skb = napi_frags_skb(napi);

	if (!skb)
		return GRO_DROP;

	if (netpoll_rx_on(skb)) {
		skb->protocol = eth_type_trans(skb, skb->dev);
		return vlan_hwaccel_receive_skb(skb, grp, vlan_tci)
			? GRO_DROP : GRO_NORMAL;
	}

	return napi_frags_finish(napi, skb,
				 vlan_gro_common(napi, grp, vlan_tci, skb));
}