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
struct sk_buff {scalar_t__ pkt_type; struct net_device* dev; struct nf_bridge_info* nf_bridge; } ;
struct nf_bridge_info {struct net_device* physindev; int /*<<< orphan*/  mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRNF_NF_BRIDGE_PREROUTING ; 
 int /*<<< orphan*/  BRNF_PKT_TYPE ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_OTHERHOST ; 
 struct net_device* bridge_parent (struct net_device*) ; 

__attribute__((used)) static struct net_device *setup_pre_routing(struct sk_buff *skb)
{
	struct nf_bridge_info *nf_bridge = skb->nf_bridge;

	if (skb->pkt_type == PACKET_OTHERHOST) {
		skb->pkt_type = PACKET_HOST;
		nf_bridge->mask |= BRNF_PKT_TYPE;
	}

	nf_bridge->mask |= BRNF_NF_BRIDGE_PREROUTING;
	nf_bridge->physindev = skb->dev;
	skb->dev = bridge_parent(skb->dev);

	return skb->dev;
}