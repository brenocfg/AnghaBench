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
struct xfrm_tunnel {int /*<<< orphan*/  (* handler ) (struct sk_buff*) ;struct xfrm_tunnel* next; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PORT_UNREACH ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 
 struct xfrm_tunnel* tunnel4_handlers ; 

__attribute__((used)) static int tunnel4_rcv(struct sk_buff *skb)
{
	struct xfrm_tunnel *handler;

	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto drop;

	for (handler = tunnel4_handlers; handler; handler = handler->next)
		if (!handler->handler(skb))
			return 0;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

drop:
	kfree_skb(skb);
	return 0;
}