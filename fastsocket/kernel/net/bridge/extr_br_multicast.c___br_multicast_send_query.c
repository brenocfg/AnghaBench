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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_bridge_port {int /*<<< orphan*/  dev; } ;
struct net_bridge {int dummy; } ;
struct ethhdr {int dummy; } ;
struct br_ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_BR_LOCAL_OUT ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_BRIDGE ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 struct sk_buff* br_multicast_alloc_query (struct net_bridge*,struct br_ip*) ; 
 int /*<<< orphan*/  dev_queue_xmit ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void __br_multicast_send_query(struct net_bridge *br,
				      struct net_bridge_port *port,
				      struct br_ip *ip)
{
	struct sk_buff *skb;

	skb = br_multicast_alloc_query(br, ip);
	if (!skb)
		return;

	if (port) {
		__skb_push(skb, sizeof(struct ethhdr));
		skb->dev = port->dev;
		NF_HOOK(PF_BRIDGE, NF_BR_LOCAL_OUT, skb, NULL, skb->dev,
			dev_queue_xmit);
	} else
		netif_rx(skb);
}