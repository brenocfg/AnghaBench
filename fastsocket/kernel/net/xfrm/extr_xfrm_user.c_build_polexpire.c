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
struct xfrm_user_polexpire {int hard; int /*<<< orphan*/  pol; } ;
struct xfrm_policy {int /*<<< orphan*/  mark; int /*<<< orphan*/  type; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct TYPE_2__ {int hard; } ;
struct km_event {int /*<<< orphan*/  pid; TYPE_1__ data; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  XFRM_MSG_POLEXPIRE ; 
 int /*<<< orphan*/  copy_to_user_policy (struct xfrm_policy*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ copy_to_user_policy_type (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ copy_to_user_sec_ctx (struct xfrm_policy*,struct sk_buff*) ; 
 scalar_t__ copy_to_user_tmpl (struct xfrm_policy*,struct sk_buff*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct xfrm_user_polexpire* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_mark_put (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_polexpire(struct sk_buff *skb, struct xfrm_policy *xp,
			   int dir, struct km_event *c)
{
	struct xfrm_user_polexpire *upe;
	struct nlmsghdr *nlh;
	int hard = c->data.hard;

	nlh = nlmsg_put(skb, c->pid, 0, XFRM_MSG_POLEXPIRE, sizeof(*upe), 0);
	if (nlh == NULL)
		return -EMSGSIZE;

	upe = nlmsg_data(nlh);
	copy_to_user_policy(xp, &upe->pol, dir);
	if (copy_to_user_tmpl(xp, skb) < 0)
		goto nlmsg_failure;
	if (copy_to_user_sec_ctx(xp, skb))
		goto nlmsg_failure;
	if (copy_to_user_policy_type(xp->type, skb) < 0)
		goto nlmsg_failure;
	if (xfrm_mark_put(skb, &xp->mark))
		goto nla_put_failure;
	upe->hard = !!hard;

	return nlmsg_end(skb, nlh);

nla_put_failure:
nlmsg_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}