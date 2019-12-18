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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nf_conntrack_l4proto {int (* to_nlattr ) (struct sk_buff*,struct nlattr*,struct nf_conn*) ;} ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int CTA_PROTOINFO ; 
 int NLA_F_NESTED ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_protonum (struct nf_conn*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 int stub1 (struct sk_buff*,struct nlattr*,struct nf_conn*) ; 

__attribute__((used)) static inline int
ctnetlink_dump_protoinfo(struct sk_buff *skb, struct nf_conn *ct)
{
	struct nf_conntrack_l4proto *l4proto;
	struct nlattr *nest_proto;
	int ret;

	l4proto = __nf_ct_l4proto_find(nf_ct_l3num(ct), nf_ct_protonum(ct));
	if (!l4proto->to_nlattr)
		return 0;

	nest_proto = nla_nest_start(skb, CTA_PROTOINFO | NLA_F_NESTED);
	if (!nest_proto)
		goto nla_put_failure;

	ret = l4proto->to_nlattr(skb, nest_proto, ct);

	nla_nest_end(skb, nest_proto);

	return ret;

nla_put_failure:
	return -1;
}