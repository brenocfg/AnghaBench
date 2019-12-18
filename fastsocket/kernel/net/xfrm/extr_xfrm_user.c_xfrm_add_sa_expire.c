#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_usersa_info {int /*<<< orphan*/  family; TYPE_1__ id; } ;
struct xfrm_user_expire {scalar_t__ hard; struct xfrm_usersa_info state; } ;
struct TYPE_6__ {scalar_t__ state; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_2__ km; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;
struct TYPE_7__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 TYPE_4__ NETLINK_CB (struct sk_buff*) ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  __xfrm_state_delete (struct xfrm_state*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  km_state_expired (struct xfrm_state*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct xfrm_user_expire* nlmsg_data (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_audit_state_delete (struct xfrm_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 struct xfrm_state* xfrm_state_lookup_with_mark (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_add_sa_expire(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_state *x;
	int err;
	struct xfrm_user_expire *ue = nlmsg_data(nlh);
	struct xfrm_usersa_info *p = &ue->state;
	struct xfrm_mark m;
	u32 mark = xfrm_mark_get(attrs, &m);;

	x = xfrm_state_lookup_with_mark(net, mark, &p->id.daddr, p->id.spi, p->id.proto, p->family);

	err = -ENOENT;
	if (x == NULL)
		return err;

	spin_lock_bh(&x->lock);
	err = -EINVAL;
	if (x->km.state != XFRM_STATE_VALID)
		goto out;
	km_state_expired(x, ue->hard, current->pid);

	if (ue->hard) {
		uid_t loginuid = NETLINK_CB(skb).loginuid;
		uid_t sessionid = NETLINK_CB(skb).sessionid;
		u32 sid = NETLINK_CB(skb).sid;
		__xfrm_state_delete(x);
		xfrm_audit_state_delete(x, 1, loginuid, sessionid, sid);
	}
	err = 0;
out:
	spin_unlock_bh(&x->lock);
	xfrm_state_put(x);
	return err;
}