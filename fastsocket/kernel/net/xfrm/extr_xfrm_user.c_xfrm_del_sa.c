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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_usersa_id {int dummy; } ;
struct xfrm_state {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct km_event {int /*<<< orphan*/  event; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 
 struct xfrm_usersa_id* nlmsg_data (struct nlmsghdr*) ; 
 int security_xfrm_state_delete (struct xfrm_state*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_audit_state_delete (struct xfrm_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfrm_state_delete (struct xfrm_state*) ; 
 scalar_t__ xfrm_state_kern (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_user_state_lookup (struct net*,struct xfrm_usersa_id*,struct nlattr**,int*) ; 

__attribute__((used)) static int xfrm_del_sa(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_state *x;
	int err = -ESRCH;
	struct km_event c;
	struct xfrm_usersa_id *p = nlmsg_data(nlh);
	uid_t loginuid = NETLINK_CB(skb).loginuid;
	u32 sessionid = NETLINK_CB(skb).sessionid;
	u32 sid = NETLINK_CB(skb).sid;

	x = xfrm_user_state_lookup(net, p, attrs, &err);
	if (x == NULL)
		return err;

	if ((err = security_xfrm_state_delete(x)) != 0)
		goto out;

	if (xfrm_state_kern(x)) {
		err = -EPERM;
		goto out;
	}

	err = xfrm_state_delete(x);

	if (err < 0)
		goto out;

	c.seq = nlh->nlmsg_seq;
	c.pid = nlh->nlmsg_pid;
	c.event = nlh->nlmsg_type;
	km_state_notify(x, &c);

out:
	xfrm_audit_state_delete(x, err ? 0 : 1, loginuid, sessionid, sid);
	xfrm_state_put(x);
	return err;
}