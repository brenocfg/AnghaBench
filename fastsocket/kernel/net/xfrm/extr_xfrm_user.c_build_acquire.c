#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfrm_user_acquire {int /*<<< orphan*/  seq; int /*<<< orphan*/  calgos; int /*<<< orphan*/  ealgos; int /*<<< orphan*/  aalgos; int /*<<< orphan*/  policy; int /*<<< orphan*/  sel; int /*<<< orphan*/  saddr; int /*<<< orphan*/  id; } ;
struct xfrm_tmpl {int /*<<< orphan*/  calgos; int /*<<< orphan*/  ealgos; int /*<<< orphan*/  aalgos; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  saddr; } ;
struct xfrm_state {TYPE_2__ km; int /*<<< orphan*/  sel; TYPE_1__ props; int /*<<< orphan*/  id; } ;
struct xfrm_policy {int /*<<< orphan*/  mark; int /*<<< orphan*/  type; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  XFRM_MSG_ACQUIRE ; 
 int /*<<< orphan*/  copy_to_user_policy (struct xfrm_policy*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ copy_to_user_policy_type (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ copy_to_user_state_sec_ctx (struct xfrm_state*,struct sk_buff*) ; 
 scalar_t__ copy_to_user_tmpl (struct xfrm_policy*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct xfrm_user_acquire* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_get_acqseq () ; 
 scalar_t__ xfrm_mark_put (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_acquire(struct sk_buff *skb, struct xfrm_state *x,
			 struct xfrm_tmpl *xt, struct xfrm_policy *xp,
			 int dir)
{
	struct xfrm_user_acquire *ua;
	struct nlmsghdr *nlh;
	__u32 seq = xfrm_get_acqseq();

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_ACQUIRE, sizeof(*ua), 0);
	if (nlh == NULL)
		return -EMSGSIZE;

	ua = nlmsg_data(nlh);
	memcpy(&ua->id, &x->id, sizeof(ua->id));
	memcpy(&ua->saddr, &x->props.saddr, sizeof(ua->saddr));
	memcpy(&ua->sel, &x->sel, sizeof(ua->sel));
	copy_to_user_policy(xp, &ua->policy, dir);
	ua->aalgos = xt->aalgos;
	ua->ealgos = xt->ealgos;
	ua->calgos = xt->calgos;
	ua->seq = x->km.seq = seq;

	if (copy_to_user_tmpl(xp, skb) < 0)
		goto nlmsg_failure;
	if (copy_to_user_state_sec_ctx(x, skb))
		goto nlmsg_failure;
	if (copy_to_user_policy_type(xp->type, skb) < 0)
		goto nlmsg_failure;
	if (xfrm_mark_put(skb, &xp->mark))
		goto nla_put_failure;

	return nlmsg_end(skb, nlh);

nla_put_failure:
nlmsg_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}