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
struct tcf_hashinfo {int hmask; struct tcf_common** htab; } ;
struct tcf_common {struct tcf_common* tcfc_next; } ;
struct tc_action {TYPE_1__* ops; int /*<<< orphan*/  order; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 scalar_t__ ACT_P_DELETED ; 
 int EINVAL ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCA_FCNT ; 
 int /*<<< orphan*/  TCA_KIND ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 size_t tcf_hash (int,int) ; 
 scalar_t__ tcf_hash_release (struct tcf_common*,int /*<<< orphan*/ ,struct tcf_hashinfo*) ; 

__attribute__((used)) static int tcf_del_walker(struct sk_buff *skb, struct tc_action *a,
			  struct tcf_hashinfo *hinfo)
{
	struct tcf_common *p, *s_p;
	struct nlattr *nest;
	int i= 0, n_i = 0;

	nest = nla_nest_start(skb, a->order);
	if (nest == NULL)
		goto nla_put_failure;
	NLA_PUT_STRING(skb, TCA_KIND, a->ops->kind);
	for (i = 0; i < (hinfo->hmask + 1); i++) {
		p = hinfo->htab[tcf_hash(i, hinfo->hmask)];

		while (p != NULL) {
			s_p = p->tcfc_next;
			if (ACT_P_DELETED == tcf_hash_release(p, 0, hinfo))
				 module_put(a->ops->owner);
			n_i++;
			p = s_p;
		}
	}
	NLA_PUT_U32(skb, TCA_FCNT, n_i);
	nla_nest_end(skb, nest);

	return n_i;
nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -EINVAL;
}