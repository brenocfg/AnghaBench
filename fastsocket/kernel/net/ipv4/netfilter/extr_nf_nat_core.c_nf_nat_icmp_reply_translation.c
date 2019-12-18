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
typedef  int /*<<< orphan*/  u_int16_t ;
struct sk_buff {scalar_t__ nfctinfo; scalar_t__ ip_summed; scalar_t__ len; scalar_t__ data; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_l4proto {int dummy; } ;
struct nf_conn {int status; TYPE_1__* tuplehash; } ;
struct iphdr {int ihl; int /*<<< orphan*/  protocol; } ;
struct icmphdr {scalar_t__ type; scalar_t__ checksum; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_2__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int CTINFO2DIR (int) ; 
 int HOOK2MANIP (unsigned int) ; 
 scalar_t__ ICMP_REDIRECT ; 
 unsigned long IPS_DST_NAT ; 
 int IPS_NAT_DONE_MASK ; 
 int IPS_NAT_MASK ; 
 unsigned long IPS_SRC_NAT ; 
 int IP_CT_DIR_ORIGINAL ; 
 int IP_CT_DIR_REPLY ; 
 scalar_t__ IP_CT_IS_REPLY ; 
 scalar_t__ IP_CT_RELATED ; 
 int IP_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 int /*<<< orphan*/  PF_INET ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_fold (int /*<<< orphan*/ ) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  l3proto ; 
 int /*<<< orphan*/  manip_pkt (int /*<<< orphan*/ ,struct sk_buff*,int,struct nf_conntrack_tuple*,int) ; 
 int /*<<< orphan*/  nf_ct_get_tuple (struct sk_buff*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_tuple*,int /*<<< orphan*/ ,struct nf_conntrack_l4proto const*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuplepr (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 scalar_t__ nf_ip_checksum (struct sk_buff*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sk_buff*,int,char*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int) ; 

int nf_nat_icmp_reply_translation(struct nf_conn *ct,
				  enum ip_conntrack_info ctinfo,
				  unsigned int hooknum,
				  struct sk_buff *skb)
{
	struct {
		struct icmphdr icmp;
		struct iphdr ip;
	} *inside;
	const struct nf_conntrack_l4proto *l4proto;
	struct nf_conntrack_tuple inner, target;
	int hdrlen = ip_hdrlen(skb);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	unsigned long statusbit;
	enum nf_nat_manip_type manip = HOOK2MANIP(hooknum);

	if (!skb_make_writable(skb, hdrlen + sizeof(*inside)))
		return 0;

	inside = (void *)skb->data + ip_hdrlen(skb);

	/* We're actually going to mangle it beyond trivial checksum
	   adjustment, so make sure the current checksum is correct. */
	if (nf_ip_checksum(skb, hooknum, hdrlen, 0))
		return 0;

	/* Must be RELATED */
	NF_CT_ASSERT(skb->nfctinfo == IP_CT_RELATED ||
		     skb->nfctinfo == IP_CT_RELATED+IP_CT_IS_REPLY);

	/* Redirects on non-null nats must be dropped, else they'll
	   start talking to each other without our translation, and be
	   confused... --RR */
	if (inside->icmp.type == ICMP_REDIRECT) {
		/* If NAT isn't finished, assume it and drop. */
		if ((ct->status & IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
			return 0;

		if (ct->status & IPS_NAT_MASK)
			return 0;
	}

	pr_debug("icmp_reply_translation: translating error %p manip %u "
		 "dir %s\n", skb, manip,
		 dir == IP_CT_DIR_ORIGINAL ? "ORIG" : "REPLY");

	/* rcu_read_lock()ed by nf_hook_slow */
	l4proto = __nf_ct_l4proto_find(PF_INET, inside->ip.protocol);

	if (!nf_ct_get_tuple(skb,
			     ip_hdrlen(skb) + sizeof(struct icmphdr),
			     (ip_hdrlen(skb) +
			      sizeof(struct icmphdr) + inside->ip.ihl * 4),
			     (u_int16_t)AF_INET,
			     inside->ip.protocol,
			     &inner, l3proto, l4proto))
		return 0;

	/* Change inner back to look like incoming packet.  We do the
	   opposite manip on this hook to normal, because it might not
	   pass all hooks (locally-generated ICMP).  Consider incoming
	   packet: PREROUTING (DST manip), routing produces ICMP, goes
	   through POSTROUTING (which must correct the DST manip). */
	if (!manip_pkt(inside->ip.protocol, skb,
		       ip_hdrlen(skb) + sizeof(inside->icmp),
		       &ct->tuplehash[!dir].tuple,
		       !manip))
		return 0;

	if (skb->ip_summed != CHECKSUM_PARTIAL) {
		/* Reloading "inside" here since manip_pkt inner. */
		inside = (void *)skb->data + ip_hdrlen(skb);
		inside->icmp.checksum = 0;
		inside->icmp.checksum =
			csum_fold(skb_checksum(skb, hdrlen,
					       skb->len - hdrlen, 0));
	}

	/* Change outer to look the reply to an incoming packet
	 * (proto 0 means don't invert per-proto part). */
	if (manip == IP_NAT_MANIP_SRC)
		statusbit = IPS_SRC_NAT;
	else
		statusbit = IPS_DST_NAT;

	/* Invert if this is reply dir. */
	if (dir == IP_CT_DIR_REPLY)
		statusbit ^= IPS_NAT_MASK;

	if (ct->status & statusbit) {
		nf_ct_invert_tuplepr(&target, &ct->tuplehash[!dir].tuple);
		if (!manip_pkt(0, skb, 0, &target, manip))
			return 0;
	}

	return 1;
}