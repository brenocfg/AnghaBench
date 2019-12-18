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
struct xfrm_userpolicy_info {int dummy; } ;
struct xfrm_policy {int /*<<< orphan*/  mark; int /*<<< orphan*/  type; } ;
struct xfrm_dump_info {int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; struct sk_buff* out_skb; struct sk_buff* in_skb; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  XFRM_MSG_NEWPOLICY ; 
 int /*<<< orphan*/  copy_to_user_policy (struct xfrm_policy*,struct xfrm_userpolicy_info*,int) ; 
 scalar_t__ copy_to_user_policy_type (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ copy_to_user_sec_ctx (struct xfrm_policy*,struct sk_buff*) ; 
 scalar_t__ copy_to_user_tmpl (struct xfrm_policy*,struct sk_buff*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct xfrm_userpolicy_info* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_mark_put (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_one_policy(struct xfrm_policy *xp, int dir, int count, void *ptr)
{
	struct xfrm_dump_info *sp = ptr;
	struct xfrm_userpolicy_info *p;
	struct sk_buff *in_skb = sp->in_skb;
	struct sk_buff *skb = sp->out_skb;
	struct nlmsghdr *nlh;

	nlh = nlmsg_put(skb, NETLINK_CB(in_skb).pid, sp->nlmsg_seq,
			XFRM_MSG_NEWPOLICY, sizeof(*p), sp->nlmsg_flags);
	if (nlh == NULL)
		return -EMSGSIZE;

	p = nlmsg_data(nlh);
	copy_to_user_policy(xp, p, dir);
	if (copy_to_user_tmpl(xp, skb) < 0)
		goto nlmsg_failure;
	if (copy_to_user_sec_ctx(xp, skb))
		goto nlmsg_failure;
	if (copy_to_user_policy_type(xp->type, skb) < 0)
		goto nlmsg_failure;
	if (xfrm_mark_put(skb, &xp->mark))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
nlmsg_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}