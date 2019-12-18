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
struct tcamsg {scalar_t__ tca__pad2; scalar_t__ tca__pad1; int /*<<< orphan*/  tca_family; } ;
struct tc_action_ops {int (* walk ) (struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct tc_action*) ;int /*<<< orphan*/  owner; int /*<<< orphan*/  kind; } ;
struct tc_action {struct tc_action_ops* ops; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_len; int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int /*<<< orphan*/  skb; struct nlmsghdr* nlh; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 TYPE_1__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 struct tcamsg* NLMSG_DATA (struct nlmsghdr*) ; 
 struct nlmsghdr* NLMSG_PUT (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_GETACTION ; 
 int /*<<< orphan*/  TCA_ACT_TAB ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 struct nlattr* find_dump_kind (struct nlmsghdr*) ; 
 struct net init_net ; 
 int /*<<< orphan*/  memset (struct tc_action*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct tc_action*) ; 
 struct tc_action_ops* tc_lookup_action (struct nlattr*) ; 

__attribute__((used)) static int
tc_dump_action(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct nlmsghdr *nlh;
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;
	struct tc_action_ops *a_o;
	struct tc_action a;
	int ret = 0;
	struct tcamsg *t = (struct tcamsg *) NLMSG_DATA(cb->nlh);
	struct nlattr *kind = find_dump_kind(cb->nlh);

	if (net != &init_net)
		return 0;

	if (kind == NULL) {
		pr_info("tc_dump_action: action bad kind\n");
		return 0;
	}

	a_o = tc_lookup_action(kind);
	if (a_o == NULL) {
		return 0;
	}

	memset(&a, 0, sizeof(struct tc_action));
	a.ops = a_o;

	if (a_o->walk == NULL) {
		WARN(1, "tc_dump_action: %s !capable of dumping table\n",
		     a_o->kind);
		goto nla_put_failure;
	}

	nlh = NLMSG_PUT(skb, NETLINK_CB(cb->skb).pid, cb->nlh->nlmsg_seq,
			cb->nlh->nlmsg_type, sizeof(*t));
	t = NLMSG_DATA(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;

	nest = nla_nest_start(skb, TCA_ACT_TAB);
	if (nest == NULL)
		goto nla_put_failure;

	ret = a_o->walk(skb, cb, RTM_GETACTION, &a);
	if (ret < 0)
		goto nla_put_failure;

	if (ret > 0) {
		nla_nest_end(skb, nest);
		ret = skb->len;
	} else
		nla_nest_cancel(skb, nest);

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	if (NETLINK_CB(cb->skb).pid && ret)
		nlh->nlmsg_flags |= NLM_F_MULTI;
	module_put(a_o->owner);
	return skb->len;

nla_put_failure:
nlmsg_failure:
	module_put(a_o->owner);
	nlmsg_trim(skb, b);
	return skb->len;
}