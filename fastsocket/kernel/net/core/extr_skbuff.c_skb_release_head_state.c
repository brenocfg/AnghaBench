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
struct sk_buff {scalar_t__ tc_verd; scalar_t__ tc_index; int /*<<< orphan*/  nf_bridge; int /*<<< orphan*/  nfct_reasm; int /*<<< orphan*/  nfct; int /*<<< orphan*/  (* destructor ) (struct sk_buff*) ;int /*<<< orphan*/  sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  nf_bridge_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_put_reasm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secpath_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static void skb_release_head_state(struct sk_buff *skb)
{
	skb_dst_drop(skb);
#ifdef CONFIG_XFRM
	secpath_put(skb->sp);
#endif
	if (skb->destructor) {
		WARN_ON(in_irq());
		skb->destructor(skb);
	}
#if defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	nf_conntrack_put(skb->nfct);
	nf_conntrack_put_reasm(skb->nfct_reasm);
#endif
#ifdef CONFIG_BRIDGE_NETFILTER
	nf_bridge_put(skb->nf_bridge);
#endif
/* XXX: IS this still necessary? - JHS */
#ifdef CONFIG_NET_SCHED
	skb->tc_index = 0;
#ifdef CONFIG_NET_CLS_ACT
	skb->tc_verd = 0;
#endif
#endif
}