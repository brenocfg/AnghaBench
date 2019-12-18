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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct fib_rules_ops {scalar_t__ (* fill ) (struct fib_rule*,struct sk_buff*,struct fib_rule_hdr*) ;int /*<<< orphan*/  family; } ;
struct fib_rule_hdr {scalar_t__ action; int /*<<< orphan*/  flags; scalar_t__ res2; scalar_t__ res1; scalar_t__ table; int /*<<< orphan*/  family; } ;
struct fib_rule {scalar_t__ action; int ifindex; scalar_t__ target; scalar_t__ mark_mask; scalar_t__ mark; scalar_t__ pref; scalar_t__* ifname; int /*<<< orphan*/ * ctarget; int /*<<< orphan*/  flags; scalar_t__ table; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  FIB_RULE_DEV_DETACHED ; 
 int /*<<< orphan*/  FIB_RULE_UNRESOLVED ; 
 int /*<<< orphan*/  FRA_FWMARK ; 
 int /*<<< orphan*/  FRA_FWMASK ; 
 int /*<<< orphan*/  FRA_GOTO ; 
 int /*<<< orphan*/  FRA_IFNAME ; 
 int /*<<< orphan*/  FRA_PRIORITY ; 
 int /*<<< orphan*/  FRA_TABLE ; 
 scalar_t__ FR_ACT_GOTO ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct fib_rule_hdr* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ stub1 (struct fib_rule*,struct sk_buff*,struct fib_rule_hdr*) ; 

__attribute__((used)) static int fib_nl_fill_rule(struct sk_buff *skb, struct fib_rule *rule,
			    u32 pid, u32 seq, int type, int flags,
			    struct fib_rules_ops *ops)
{
	struct nlmsghdr *nlh;
	struct fib_rule_hdr *frh;

	nlh = nlmsg_put(skb, pid, seq, type, sizeof(*frh), flags);
	if (nlh == NULL)
		return -EMSGSIZE;

	frh = nlmsg_data(nlh);
	frh->family = ops->family;
	frh->table = rule->table;
	NLA_PUT_U32(skb, FRA_TABLE, rule->table);
	frh->res1 = 0;
	frh->res2 = 0;
	frh->action = rule->action;
	frh->flags = rule->flags;

	if (rule->action == FR_ACT_GOTO && rule->ctarget == NULL)
		frh->flags |= FIB_RULE_UNRESOLVED;

	if (rule->ifname[0]) {
		NLA_PUT_STRING(skb, FRA_IFNAME, rule->ifname);

		if (rule->ifindex == -1)
			frh->flags |= FIB_RULE_DEV_DETACHED;
	}

	if (rule->pref)
		NLA_PUT_U32(skb, FRA_PRIORITY, rule->pref);

	if (rule->mark)
		NLA_PUT_U32(skb, FRA_FWMARK, rule->mark);

	if (rule->mark_mask || rule->mark)
		NLA_PUT_U32(skb, FRA_FWMASK, rule->mark_mask);

	if (rule->target)
		NLA_PUT_U32(skb, FRA_GOTO, rule->target);

	if (ops->fill(rule, skb, frh) < 0)
		goto nla_put_failure;

	return nlmsg_end(skb, nlh);

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}