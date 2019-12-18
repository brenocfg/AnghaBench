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
struct tcf_common {struct tcf_common* tcfc_next; } ;
struct tc_action {int order; struct tcf_common* priv; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int* args; } ;

/* Variables and functions */
 int POL_TAB_MASK ; 
 int RTM_DELACTION ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 int /*<<< orphan*/  police_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_action_dump_1 (struct sk_buff*,struct tc_action*,int /*<<< orphan*/ ,int) ; 
 size_t tcf_hash (int,int) ; 
 struct tcf_common** tcf_police_ht ; 

__attribute__((used)) static int tcf_act_police_walker(struct sk_buff *skb, struct netlink_callback *cb,
			      int type, struct tc_action *a)
{
	struct tcf_common *p;
	int err = 0, index = -1, i = 0, s_i = 0, n_i = 0;
	struct nlattr *nest;

	read_lock_bh(&police_lock);

	s_i = cb->args[0];

	for (i = 0; i < (POL_TAB_MASK + 1); i++) {
		p = tcf_police_ht[tcf_hash(i, POL_TAB_MASK)];

		for (; p; p = p->tcfc_next) {
			index++;
			if (index < s_i)
				continue;
			a->priv = p;
			a->order = index;
			nest = nla_nest_start(skb, a->order);
			if (nest == NULL)
				goto nla_put_failure;
			if (type == RTM_DELACTION)
				err = tcf_action_dump_1(skb, a, 0, 1);
			else
				err = tcf_action_dump_1(skb, a, 0, 0);
			if (err < 0) {
				index--;
				nla_nest_cancel(skb, nest);
				goto done;
			}
			nla_nest_end(skb, nest);
			n_i++;
		}
	}
done:
	read_unlock_bh(&police_lock);
	if (n_i)
		cb->args[0] += n_i;
	return n_i;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	goto done;
}