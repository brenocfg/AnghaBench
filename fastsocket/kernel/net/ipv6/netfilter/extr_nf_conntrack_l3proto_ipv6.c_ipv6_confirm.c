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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_helper {unsigned int (* help ) (struct sk_buff*,int,struct nf_conn*,int) ;int /*<<< orphan*/  name; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int dummy; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 int IP_CT_IS_REPLY ; 
 int IP_CT_RELATED ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 unsigned int NF_ACCEPT ; 
 int htons (int) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_skip_exthdr_fragoff (struct sk_buff*,int,int /*<<< orphan*/ *,int*) ; 
 unsigned int nf_conntrack_confirm (struct sk_buff*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_log_packet (int /*<<< orphan*/ ,unsigned int,struct sk_buff*,struct net_device const*,struct net_device const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct nf_conntrack_helper* rcu_dereference (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct sk_buff*,int,struct nf_conn*,int) ; 

__attribute__((used)) static unsigned int ipv6_confirm(unsigned int hooknum,
				 struct sk_buff *skb,
				 const struct net_device *in,
				 const struct net_device *out,
				 int (*okfn)(struct sk_buff *))
{
	struct nf_conn *ct;
	const struct nf_conn_help *help;
	const struct nf_conntrack_helper *helper;
	enum ip_conntrack_info ctinfo;
	unsigned int ret;
	__be16 frag_off;
	int protoff;
	u8 nexthdr;

	/* This is where we call the helper: as the packet goes out. */
	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || ctinfo == IP_CT_RELATED + IP_CT_IS_REPLY)
		goto out;

	help = nfct_help(ct);
	if (!help)
		goto out;
	/* rcu_read_lock()ed by nf_hook_slow */
	helper = rcu_dereference(help->helper);
	if (!helper)
		goto out;

	nexthdr = ipv6_hdr(skb)->nexthdr;
	protoff = ipv6_skip_exthdr_fragoff(skb, sizeof(struct ipv6hdr),
					   &nexthdr, &frag_off);
	if (protoff < 0 || (frag_off & htons(~0x7)) != 0) {
		pr_debug("proto header not found\n");
		return NF_ACCEPT;
	}

	ret = helper->help(skb, protoff, ct, ctinfo);
	if (ret != NF_ACCEPT) {
		nf_log_packet(NFPROTO_IPV6, hooknum, skb, in, out, NULL,
			      "nf_ct_%s: dropping packet", helper->name);
		return ret;
	}
out:
	/* We've seen it coming out the other side: confirm it */
	return nf_conntrack_confirm(skb);
}