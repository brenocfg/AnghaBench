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
struct tc_action {TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kind; int /*<<< orphan*/ * dump; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_KIND ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ tcf_action_copy_stats (struct sk_buff*,struct tc_action*,int /*<<< orphan*/ ) ; 
 int tcf_action_dump_old (struct sk_buff*,struct tc_action*,int,int) ; 

int
tcf_action_dump_1(struct sk_buff *skb, struct tc_action *a, int bind, int ref)
{
	int err = -EINVAL;
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;

	if (a->ops == NULL || a->ops->dump == NULL)
		return err;

	NLA_PUT_STRING(skb, TCA_KIND, a->ops->kind);
	if (tcf_action_copy_stats(skb, a, 0))
		goto nla_put_failure;
	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;
	if ((err = tcf_action_dump_old(skb, a, bind, ref)) > 0) {
		nla_nest_end(skb, nest);
		return err;
	}

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}