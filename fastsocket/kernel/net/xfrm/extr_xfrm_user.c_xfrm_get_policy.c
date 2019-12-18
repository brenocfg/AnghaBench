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
struct xfrm_userpolicy_id {int /*<<< orphan*/  dir; scalar_t__ index; int /*<<< orphan*/  sel; } ;
struct xfrm_user_sec_ctx {int dummy; } ;
struct xfrm_sec_ctx {int dummy; } ;
struct xfrm_policy {int dummy; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_1__ xfrm; } ;
struct TYPE_5__ {scalar_t__ byid; } ;
struct km_event {scalar_t__ event; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; TYPE_2__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 TYPE_3__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 size_t XFRMA_SEC_CTX ; 
 scalar_t__ XFRM_MSG_DELPOLICY ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int copy_from_user_policy_type (int /*<<< orphan*/ *,struct nlattr**) ; 
 int /*<<< orphan*/  km_policy_notify (struct xfrm_policy*,int /*<<< orphan*/ ,struct km_event*) ; 
 struct xfrm_user_sec_ctx* nla_data (struct nlattr*) ; 
 struct xfrm_userpolicy_id* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int security_xfrm_policy_alloc (struct xfrm_sec_ctx**,struct xfrm_user_sec_ctx*) ; 
 int /*<<< orphan*/  security_xfrm_policy_free (struct xfrm_sec_ctx*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int verify_policy_dir (int /*<<< orphan*/ ) ; 
 int verify_sec_ctx_len (struct nlattr**) ; 
 int /*<<< orphan*/  xfrm_audit_policy_delete (struct xfrm_policy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_byid (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 struct xfrm_policy* xfrm_policy_bysel_ctx (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xfrm_sec_ctx*,int,int*) ; 
 struct sk_buff* xfrm_policy_netlink (struct sk_buff*,struct xfrm_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_get_policy(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_policy *xp;
	struct xfrm_userpolicy_id *p;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	int err;
	struct km_event c;
	int delete;
	struct xfrm_mark m;
	u32 mark = xfrm_mark_get(attrs, &m);

	p = nlmsg_data(nlh);
	delete = nlh->nlmsg_type == XFRM_MSG_DELPOLICY;

	err = copy_from_user_policy_type(&type, attrs);
	if (err)
		return err;

	err = verify_policy_dir(p->dir);
	if (err)
		return err;

	if (p->index)
		xp = xfrm_policy_byid(net, mark, type, p->dir, p->index, delete, &err);
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
		xp = xfrm_policy_bysel_ctx(net, mark, type, p->dir, &p->sel,
					   ctx, delete, &err);
		security_xfrm_policy_free(ctx);
	}
	if (xp == NULL)
		return -ENOENT;

	if (!delete) {
		struct sk_buff *resp_skb;

		resp_skb = xfrm_policy_netlink(skb, xp, p->dir, nlh->nlmsg_seq);
		if (IS_ERR(resp_skb)) {
			err = PTR_ERR(resp_skb);
		} else {
			err = nlmsg_unicast(net->xfrm.nlsk, resp_skb,
					    NETLINK_CB(skb).pid);
		}
	} else {
		uid_t loginuid = NETLINK_CB(skb).loginuid;
		u32 sessionid = NETLINK_CB(skb).sessionid;
		u32 sid = NETLINK_CB(skb).sid;

		xfrm_audit_policy_delete(xp, err ? 0 : 1, loginuid, sessionid,
					 sid);

		if (err != 0)
			goto out;

		c.data.byid = p->index;
		c.event = nlh->nlmsg_type;
		c.seq = nlh->nlmsg_seq;
		c.pid = nlh->nlmsg_pid;
		km_policy_notify(xp, p->dir, &c);
	}

out:
	xfrm_pol_put(xp);
	return err;
}