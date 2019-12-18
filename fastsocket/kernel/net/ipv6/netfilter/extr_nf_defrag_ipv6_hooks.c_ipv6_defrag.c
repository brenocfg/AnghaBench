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
struct sk_buff {scalar_t__ nfct; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_HOOK_THRESH (int /*<<< orphan*/ ,unsigned int,struct sk_buff*,struct net_device*,struct net_device*,int (*) (struct sk_buff*),scalar_t__) ; 
 scalar_t__ NF_IP6_PRI_CONNTRACK_DEFRAG ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  nf_ct6_defrag_user (unsigned int,struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_frag6_consume_orig (struct sk_buff*) ; 
 struct sk_buff* nf_ct_frag6_gather (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ipv6_defrag(unsigned int hooknum,
				struct sk_buff *skb,
				const struct net_device *in,
				const struct net_device *out,
				int (*okfn)(struct sk_buff *))
{
	struct sk_buff *reasm;

	/* Previously seen (loopback)?	*/
	if (skb->nfct)
		return NF_ACCEPT;

	reasm = nf_ct_frag6_gather(skb, nf_ct6_defrag_user(hooknum, skb));
	/* queued */
	if (reasm == NULL)
		return NF_STOLEN;

	/* error occured or not fragmented */
	if (reasm == skb)
		return NF_ACCEPT;

	nf_ct_frag6_consume_orig(reasm);

	NF_HOOK_THRESH(PF_INET6, hooknum, reasm,
		       (struct net_device *) in, (struct net_device *) out,
		       okfn, NF_IP6_PRI_CONNTRACK_DEFRAG + 1);

	return NF_STOLEN;
}