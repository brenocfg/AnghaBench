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
typedef  int /*<<< orphan*/  u32 ;
struct tcamsg {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EAGAIN ; 
 int EINVAL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_REPLACE ; 
#define  RTM_DELACTION 130 
#define  RTM_GETACTION 129 
#define  RTM_NEWACTION 128 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 size_t TCA_ACT_TAB ; 
 struct net init_net ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int tca_action_gd (struct nlattr*,struct nlmsghdr*,int /*<<< orphan*/ ,int const) ; 
 int tcf_action_add (struct nlattr*,struct nlmsghdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc_ctl_action(struct sk_buff *skb, struct nlmsghdr *n, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_ACT_MAX + 1];
	u32 pid = skb ? NETLINK_CB(skb).pid : 0;
	int ret = 0, ovr = 0;

	if (net != &init_net)
		return -EINVAL;

	ret = nlmsg_parse(n, sizeof(struct tcamsg), tca, TCA_ACT_MAX, NULL);
	if (ret < 0)
		return ret;

	if (tca[TCA_ACT_TAB] == NULL) {
		pr_notice("tc_ctl_action: received NO action attribs\n");
		return -EINVAL;
	}

	/* n->nlmsg_flags&NLM_F_CREATE
	 * */
	switch (n->nlmsg_type) {
	case RTM_NEWACTION:
		/* we are going to assume all other flags
		 * imply create only if it doesnt exist
		 * Note that CREATE | EXCL implies that
		 * but since we want avoid ambiguity (eg when flags
		 * is zero) then just set this
		 */
		if (n->nlmsg_flags&NLM_F_REPLACE)
			ovr = 1;
replay:
		ret = tcf_action_add(tca[TCA_ACT_TAB], n, pid, ovr);
		if (ret == -EAGAIN)
			goto replay;
		break;
	case RTM_DELACTION:
		ret = tca_action_gd(tca[TCA_ACT_TAB], n, pid, RTM_DELACTION);
		break;
	case RTM_GETACTION:
		ret = tca_action_gd(tca[TCA_ACT_TAB], n, pid, RTM_GETACTION);
		break;
	default:
		BUG();
	}

	return ret;
}