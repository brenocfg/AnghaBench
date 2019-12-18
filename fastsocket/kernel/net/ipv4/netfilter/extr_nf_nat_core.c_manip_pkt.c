#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct sk_buff {scalar_t__ data; } ;
struct nf_nat_protocol {int /*<<< orphan*/  (* manip_pkt ) (struct sk_buff*,unsigned int,struct nf_conntrack_tuple const*,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {TYPE_3__ u3; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_2__ src; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  check; int /*<<< orphan*/  saddr; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 int IP_NAT_MANIP_SRC ; 
 struct nf_nat_protocol* __nf_nat_proto_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_replace4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,unsigned int,struct nf_conntrack_tuple const*,int) ; 

__attribute__((used)) static bool
manip_pkt(u_int16_t proto,
	  struct sk_buff *skb,
	  unsigned int iphdroff,
	  const struct nf_conntrack_tuple *target,
	  enum nf_nat_manip_type maniptype)
{
	struct iphdr *iph;
	const struct nf_nat_protocol *p;

	if (!skb_make_writable(skb, iphdroff + sizeof(*iph)))
		return false;

	iph = (void *)skb->data + iphdroff;

	/* Manipulate protcol part. */

	/* rcu_read_lock()ed by nf_hook_slow */
	p = __nf_nat_proto_find(proto);
	if (!p->manip_pkt(skb, iphdroff, target, maniptype))
		return false;

	iph = (void *)skb->data + iphdroff;

	if (maniptype == IP_NAT_MANIP_SRC) {
		csum_replace4(&iph->check, iph->saddr, target->src.u3.ip);
		iph->saddr = target->src.u3.ip;
	} else {
		csum_replace4(&iph->check, iph->daddr, target->dst.u3.ip);
		iph->daddr = target->dst.u3.ip;
	}
	return true;
}