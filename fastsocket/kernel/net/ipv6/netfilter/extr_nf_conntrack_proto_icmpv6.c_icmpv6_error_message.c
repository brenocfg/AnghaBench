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
struct sk_buff {int nfctinfo; int /*<<< orphan*/ * nfct; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  protonum; } ;
struct nf_conntrack_tuple {TYPE_1__ dst; } ;
struct nf_conntrack_l4proto {int dummy; } ;
struct net {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct icmp6hdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_4__ {int /*<<< orphan*/  ct_general; } ;

/* Variables and functions */
 scalar_t__ IP_CT_DIR_REPLY ; 
 scalar_t__ IP_CT_IS_REPLY ; 
 int IP_CT_RELATED ; 
 int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ NF_CT_DIRECTION (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  PF_INET6 ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_conntrack_l3proto_ipv6 ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,int /*<<< orphan*/ *,struct nf_conntrack_l4proto const*) ; 
 TYPE_2__* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static int
icmpv6_error_message(struct net *net,
		     struct sk_buff *skb,
		     unsigned int icmp6off,
		     enum ip_conntrack_info *ctinfo,
		     unsigned int hooknum)
{
	struct nf_conntrack_tuple intuple, origtuple;
	const struct nf_conntrack_tuple_hash *h;
	const struct nf_conntrack_l4proto *inproto;

	NF_CT_ASSERT(skb->nfct == NULL);

	/* Are they talking about one of our connections? */
	if (!nf_ct_get_tuplepr(skb,
			       skb_network_offset(skb)
				+ sizeof(struct ipv6hdr)
				+ sizeof(struct icmp6hdr),
			       PF_INET6, &origtuple)) {
		pr_debug("icmpv6_error: Can't get tuple\n");
		return -NF_ACCEPT;
	}

	/* rcu_read_lock()ed by nf_hook_slow */
	inproto = __nf_ct_l4proto_find(PF_INET6, origtuple.dst.protonum);

	/* Ordinarily, we'd expect the inverted tupleproto, but it's
	   been preserved inside the ICMP. */
	if (!nf_ct_invert_tuple(&intuple, &origtuple,
				&nf_conntrack_l3proto_ipv6, inproto)) {
		pr_debug("icmpv6_error: Can't invert tuple\n");
		return -NF_ACCEPT;
	}

	*ctinfo = IP_CT_RELATED;

	h = nf_conntrack_find_get(net, &intuple);
	if (!h) {
		pr_debug("icmpv6_error: no match\n");
		return -NF_ACCEPT;
	} else {
		if (NF_CT_DIRECTION(h) == IP_CT_DIR_REPLY)
			*ctinfo += IP_CT_IS_REPLY;
	}

	/* Update skb to refer to this connection */
	skb->nfct = &nf_ct_tuplehash_to_ctrack(h)->ct_general;
	skb->nfctinfo = *ctinfo;
	return NF_ACCEPT;
}