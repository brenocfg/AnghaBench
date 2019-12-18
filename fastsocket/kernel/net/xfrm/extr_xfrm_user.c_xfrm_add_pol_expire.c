#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_userpolicy_info {int /*<<< orphan*/  dir; int /*<<< orphan*/  sel; scalar_t__ index; } ;
struct xfrm_user_sec_ctx {int dummy; } ;
struct xfrm_user_polexpire {scalar_t__ hard; struct xfrm_userpolicy_info pol; } ;
struct xfrm_sec_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dead; } ;
struct xfrm_policy {TYPE_1__ walk; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_3__ NETLINK_CB (struct sk_buff*) ; 
 size_t XFRMA_SEC_CTX ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int copy_from_user_policy_type (int /*<<< orphan*/ *,struct nlattr**) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  km_policy_expired (struct xfrm_policy*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct xfrm_user_sec_ctx* nla_data (struct nlattr*) ; 
 struct xfrm_user_polexpire* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int security_xfrm_policy_alloc (struct xfrm_sec_ctx**,struct xfrm_user_sec_ctx*) ; 
 int /*<<< orphan*/  security_xfrm_policy_free (struct xfrm_sec_ctx*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int verify_policy_dir (int /*<<< orphan*/ ) ; 
 int verify_sec_ctx_len (struct nlattr**) ; 
 int /*<<< orphan*/  xfrm_audit_policy_delete (struct xfrm_policy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_byid (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 struct xfrm_policy* xfrm_policy_bysel_ctx (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xfrm_sec_ctx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfrm_policy_delete (struct xfrm_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_add_pol_expire(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_policy *xp;
	struct xfrm_user_polexpire *up = nlmsg_data(nlh);
	struct xfrm_userpolicy_info *p = &up->pol;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	int err = -ENOENT;
	struct xfrm_mark m;
	u32 mark = xfrm_mark_get(attrs, &m);

	err = copy_from_user_policy_type(&type, attrs);
	if (err)
		return err;

	err = verify_policy_dir(p->dir);
	if (err)
		return err;

	if (p->index)
		xp = xfrm_policy_byid(net, mark, type, p->dir, p->index, 0, &err);
	else {
		struct nlattr *rt = attrs[XFRMA_SEC_CTX];
		struct xfrm_sec_ctx *ctx;

		err = verify_sec_ctx_len(attrs);
		if (err)
			return err;

		ctx = NULL;
		if (rt) {
			struct xfrm_user_sec_ctx *uctx = nla_data(rt);

			err = security_xfrm_policy_alloc(&ctx, uctx);
			if (err)
				return err;
		}
		xp = xfrm_policy_bysel_ctx(net, mark, type, p->dir,
					   &p->sel, ctx, 0, &err);
		security_xfrm_policy_free(ctx);
	}
	if (xp == NULL)
		return -ENOENT;

	if (unlikely(xp->walk.dead))
		goto out;

	err = 0;
	if (up->hard) {
		uid_t loginuid = NETLINK_CB(skb).loginuid;
		uid_t sessionid = NETLINK_CB(skb).sessionid;
		u32 sid = NETLINK_CB(skb).sid;
		xfrm_policy_delete(xp, p->dir);
		xfrm_audit_policy_delete(xp, 1, loginuid, sessionid, sid);

	} else {
		// reset the timers here?
		printk("Dont know what to do with soft policy expire\n");
	}
	km_policy_expired(xp, p->dir, up->hard, current->pid);

out:
	xfrm_pol_put(xp);
	return err;
}