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
struct TYPE_3__ {int /*<<< orphan*/  node; } ;
struct ipxhdr {TYPE_1__ ipx_dest; } ;
struct ipx_route {int /*<<< orphan*/  ir_intrfc; int /*<<< orphan*/  ir_router_node; scalar_t__ ir_routed; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipx_dest_net; } ;

/* Variables and functions */
 TYPE_2__* IPX_SKB_CB (struct sk_buff*) ; 
 struct ipxhdr* ipx_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipxitf_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxitf_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxitf_send (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ipx_route* ipxrtr_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxrtr_put (struct ipx_route*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int ipxrtr_route_skb(struct sk_buff *skb)
{
	struct ipxhdr *ipx = ipx_hdr(skb);
	struct ipx_route *r = ipxrtr_lookup(IPX_SKB_CB(skb)->ipx_dest_net);

	if (!r) {	/* no known route */
		kfree_skb(skb);
		return 0;
	}

	ipxitf_hold(r->ir_intrfc);
	ipxitf_send(r->ir_intrfc, skb, r->ir_routed ?
			r->ir_router_node : ipx->ipx_dest.node);
	ipxitf_put(r->ir_intrfc);
	ipxrtr_put(r);

	return 0;
}