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
struct icmphdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_4__ {int /*<<< orphan*/  ct_general; } ;

/* Variables and functions */
 scalar_t__ IP_CT_DIR_REPLY ; 
 scalar_t__ IP_CT_IS_REPLY ; 
 int IP_CT_RELATED ; 
 int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ NF_CT_DIRECTION (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  PF_INET ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_hdrlen (struct sk_buff*) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_conntrack_l3proto_ipv4 ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,int /*<<< orphan*/ *,struct nf_conntrack_l4proto const*) ; 
 TYPE_2__* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static int
icmp_error_message(struct net *net, struct sk_buff *skb,
		 enum ip_conntrack_info *ctinfo,
		 unsigned int hooknum)
{
	struct nf_conntrack_tuple innertuple, origtuple;
	const struct nf_conntrack_l4proto *innerproto;
	const struct nf_conntrack_tuple_hash *h;

	NF_CT_ASSERT(skb->nfct == NULL);

	/* Are they talking about one of our connections? */
	if (!nf_ct_get_tuplepr(skb,
			       skb_network_offset(skb) + ip_hdrlen(skb)
						       + sizeof(struct icmphdr),
			       PF_INET, &origtuple)) {
		pr_debug("icmp_error_message: failed to get tuple\n");
		return -NF_ACCEPT;
	}

	/* rcu_read_lock()ed by nf_hook_slow */
	innerproto = __nf_ct_l4proto_find(PF_INET, origtuple.dst.protonum);

	/* Ordinarily, we'd expect the inverted tupleproto, but it's
	   been preserved inside the ICMP. */
	if (!nf_ct_invert_tuple(&innertuple, &origtuple,
				&nf_conntrack_l3proto_ipv4, innerproto)) {
		pr_debug("icmp_error_message: no match\n");
		return -NF_ACCEPT;
	}

	*ctinfo = IP_CT_RELATED;

	h = nf_conntrack_find_get(net, &innertuple);
	if (!h) {
		pr_debug("icmp_error_message: no match\n");
		return -NF_ACCEPT;
	}

	if (NF_CT_DIRECTION(h) == IP_CT_DIR_REPLY)
		*ctinfo += IP_CT_IS_REPLY;

	/* Update skb to refer to this connection */
	skb->nfct = &nf_ct_tuplehash_to_ctrack(h)->ct_general;
	skb->nfctinfo = *ctinfo;
	return NF_ACCEPT;
}