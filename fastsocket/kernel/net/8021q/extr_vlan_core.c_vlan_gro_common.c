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
typedef  int u16 ;
struct vlan_group {int dummy; } ;
struct sk_buff {int deliver_no_wcard; struct net_device* dev; struct sk_buff* next; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  iif; } ;
struct net_device {int flags; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  master; } ;
struct napi_struct {struct sk_buff* gro_list; } ;
typedef  int /*<<< orphan*/  gro_result_t ;
struct TYPE_2__ {int same_flow; scalar_t__ flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRO_DROP ; 
 int IFF_PROMISC ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 unsigned int VLAN_VID_MASK ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  compare_ether_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 scalar_t__ skb_bond_should_drop (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_gro_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 struct net_device* vlan_group_get_device (struct vlan_group*,int) ; 

__attribute__((used)) static gro_result_t
vlan_gro_common(struct napi_struct *napi, struct vlan_group *grp,
		unsigned int vlan_tci, struct sk_buff *skb)
{
	struct sk_buff *p;
	struct net_device *vlan_dev;
	u16 vlan_id;

	if (skb_bond_should_drop(skb, ACCESS_ONCE(skb->dev->master)))
		skb->deliver_no_wcard = 1;

	skb->iif = skb->dev->ifindex;
	__vlan_hwaccel_put_tag(skb, vlan_tci);
	vlan_id = vlan_tci & VLAN_VID_MASK;
	vlan_dev = vlan_group_get_device(grp, vlan_id);

	if (vlan_dev)
		skb->dev = vlan_dev;
	else if (vlan_id) {
		if (!(skb->dev->flags & IFF_PROMISC))
			goto drop;
		skb->pkt_type = PACKET_OTHERHOST;
	}

	for (p = napi->gro_list; p; p = p->next) {
		NAPI_GRO_CB(p)->same_flow =
			p->dev == skb->dev && !compare_ether_header(
				skb_mac_header(p), skb_gro_mac_header(skb));
		NAPI_GRO_CB(p)->flush = 0;
	}

	return dev_gro_receive(napi, skb);

drop:
	return GRO_DROP;
}