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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {scalar_t__ state; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_2__ km; } ;
struct xfrm_mark {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  family; int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_aevent_id {TYPE_1__ sa_id; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  aevent; } ;
struct km_event {TYPE_3__ data; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int NLM_F_REPLACE ; 
 size_t XFRMA_LTIME_VAL ; 
 size_t XFRMA_REPLAY_VAL ; 
 int /*<<< orphan*/  XFRM_AE_CU ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 
 struct xfrm_aevent_id* nlmsg_data (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 struct xfrm_state* xfrm_state_lookup_with_mark (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_update_ae_params (struct xfrm_state*,struct nlattr**) ; 

__attribute__((used)) static int xfrm_new_ae(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_state *x;
	struct km_event c;
	int err = - EINVAL;
	u32 mark = 0;
	struct xfrm_mark m;
	struct xfrm_aevent_id *p = nlmsg_data(nlh);
	struct nlattr *rp = attrs[XFRMA_REPLAY_VAL];
	struct nlattr *lt = attrs[XFRMA_LTIME_VAL];

	if (!lt && !rp)
		return err;

	/* pedantic mode - thou shalt sayeth replaceth */
	if (!(nlh->nlmsg_flags&NLM_F_REPLACE))
		return err;

	mark = xfrm_mark_get(attrs, &m);

	x = xfrm_state_lookup_with_mark(net, mark, &p->sa_id.daddr, p->sa_id.spi, p->sa_id.proto, p->sa_id.family);
	if (x == NULL)
		return -ESRCH;

	if (x->km.state != XFRM_STATE_VALID)
		goto out;

	spin_lock_bh(&x->lock);
	xfrm_update_ae_params(x, attrs);
	spin_unlock_bh(&x->lock);

	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.pid = nlh->nlmsg_pid;
	c.data.aevent = XFRM_AE_CU;
	km_state_notify(x, &c);
	err = 0;
out:
	xfrm_state_put(x);
	return err;
}