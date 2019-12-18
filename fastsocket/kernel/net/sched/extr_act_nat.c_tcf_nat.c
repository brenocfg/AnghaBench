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
struct udphdr {int /*<<< orphan*/  check; } ;
struct tcphdr {int /*<<< orphan*/  check; } ;
struct tcf_result {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  drops; } ;
struct TYPE_5__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  lastuse; } ;
struct tcf_nat {int old_addr; int new_addr; int mask; int flags; int tcf_action; int /*<<< orphan*/  tcf_lock; TYPE_3__ tcf_qstats; TYPE_2__ tcf_bstats; TYPE_1__ tcf_tm; } ;
struct tc_action {struct tcf_nat* priv; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iphdr {int saddr; int daddr; int ihl; int frag_off; int protocol; int /*<<< orphan*/  check; } ;
struct icmphdr {int /*<<< orphan*/  checksum; int /*<<< orphan*/  type; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CSUM_MANGLED_0 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PARAMETERPROB ; 
 int /*<<< orphan*/  ICMP_TIME_EXCEEDED ; 
#define  IPPROTO_ICMP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  IP_OFFSET ; 
 int TCA_NAT_FLAG_EGRESS ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  csum_replace4 (int /*<<< orphan*/ *,int,int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,int,int,int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_clone_writable (struct sk_buff*,int) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_nat(struct sk_buff *skb, struct tc_action *a,
		   struct tcf_result *res)
{
	struct tcf_nat *p = a->priv;
	struct iphdr *iph;
	__be32 old_addr;
	__be32 new_addr;
	__be32 mask;
	__be32 addr;
	int egress;
	int action;
	int ihl;

	spin_lock(&p->tcf_lock);

	p->tcf_tm.lastuse = jiffies;
	old_addr = p->old_addr;
	new_addr = p->new_addr;
	mask = p->mask;
	egress = p->flags & TCA_NAT_FLAG_EGRESS;
	action = p->tcf_action;

	p->tcf_bstats.bytes += qdisc_pkt_len(skb);
	p->tcf_bstats.packets++;

	spin_unlock(&p->tcf_lock);

	if (unlikely(action == TC_ACT_SHOT))
		goto drop;

	if (!pskb_may_pull(skb, sizeof(*iph)))
		goto drop;

	iph = ip_hdr(skb);

	if (egress)
		addr = iph->saddr;
	else
		addr = iph->daddr;

	if (!((old_addr ^ addr) & mask)) {
		if (skb_cloned(skb) &&
		    !skb_clone_writable(skb, sizeof(*iph)) &&
		    pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
			goto drop;

		new_addr &= mask;
		new_addr |= addr & ~mask;

		/* Rewrite IP header */
		iph = ip_hdr(skb);
		if (egress)
			iph->saddr = new_addr;
		else
			iph->daddr = new_addr;

		csum_replace4(&iph->check, addr, new_addr);
	}

	ihl = iph->ihl * 4;

	/* It would be nice to share code with stateful NAT. */
	switch (iph->frag_off & htons(IP_OFFSET) ? 0 : iph->protocol) {
	case IPPROTO_TCP:
	{
		struct tcphdr *tcph;

		if (!pskb_may_pull(skb, ihl + sizeof(*tcph)) ||
		    (skb_cloned(skb) &&
		     !skb_clone_writable(skb, ihl + sizeof(*tcph)) &&
		     pskb_expand_head(skb, 0, 0, GFP_ATOMIC)))
			goto drop;

		tcph = (void *)(skb_network_header(skb) + ihl);
		inet_proto_csum_replace4(&tcph->check, skb, addr, new_addr, 1);
		break;
	}
	case IPPROTO_UDP:
	{
		struct udphdr *udph;

		if (!pskb_may_pull(skb, ihl + sizeof(*udph)) ||
		    (skb_cloned(skb) &&
		     !skb_clone_writable(skb, ihl + sizeof(*udph)) &&
		     pskb_expand_head(skb, 0, 0, GFP_ATOMIC)))
			goto drop;

		udph = (void *)(skb_network_header(skb) + ihl);
		if (udph->check || skb->ip_summed == CHECKSUM_PARTIAL) {
			inet_proto_csum_replace4(&udph->check, skb, addr,
						 new_addr, 1);
			if (!udph->check)
				udph->check = CSUM_MANGLED_0;
		}
		break;
	}
	case IPPROTO_ICMP:
	{
		struct icmphdr *icmph;

		if (!pskb_may_pull(skb, ihl + sizeof(*icmph) + sizeof(*iph)))
			goto drop;

		icmph = (void *)(skb_network_header(skb) + ihl);

		if ((icmph->type != ICMP_DEST_UNREACH) &&
		    (icmph->type != ICMP_TIME_EXCEEDED) &&
		    (icmph->type != ICMP_PARAMETERPROB))
			break;

		iph = (void *)(icmph + 1);
		if (egress)
			addr = iph->daddr;
		else
			addr = iph->saddr;

		if ((old_addr ^ addr) & mask)
			break;

		if (skb_cloned(skb) &&
		    !skb_clone_writable(skb,
					ihl + sizeof(*icmph) + sizeof(*iph)) &&
		    pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
			goto drop;

		icmph = (void *)(skb_network_header(skb) + ihl);
		iph = (void *)(icmph + 1);

		new_addr &= mask;
		new_addr |= addr & ~mask;

		/* XXX Fix up the inner checksums. */
		if (egress)
			iph->daddr = new_addr;
		else
			iph->saddr = new_addr;

		inet_proto_csum_replace4(&icmph->checksum, skb, addr, new_addr,
					 1);
		break;
	}
	default:
		break;
	}

	return action;

drop:
	spin_lock(&p->tcf_lock);
	p->tcf_qstats.drops++;
	spin_unlock(&p->tcf_lock);
	return TC_ACT_SHOT;
}