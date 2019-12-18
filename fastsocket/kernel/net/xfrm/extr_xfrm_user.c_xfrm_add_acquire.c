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
struct xfrm_user_tmpl {int /*<<< orphan*/  family; } ;
struct xfrm_user_acquire {int /*<<< orphan*/  calgos; int /*<<< orphan*/  ealgos; int /*<<< orphan*/  aalgos; int /*<<< orphan*/  sel; int /*<<< orphan*/  saddr; int /*<<< orphan*/  id; int /*<<< orphan*/  policy; } ;
struct xfrm_tmpl {int /*<<< orphan*/  calgos; int /*<<< orphan*/  ealgos; int /*<<< orphan*/  aalgos; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  family; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; int /*<<< orphan*/  saddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  v; int /*<<< orphan*/  m; } ;
struct xfrm_state {int xfrm_nr; TYPE_2__ props; int /*<<< orphan*/  id; struct xfrm_tmpl* xfrm_vec; TYPE_1__ mark; int /*<<< orphan*/  sel; } ;
struct xfrm_policy {int xfrm_nr; TYPE_2__ props; int /*<<< orphan*/  id; struct xfrm_tmpl* xfrm_vec; TYPE_1__ mark; int /*<<< orphan*/  sel; } ;
struct xfrm_mark {int /*<<< orphan*/  v; int /*<<< orphan*/  m; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t XFRMA_TMPL ; 
 int /*<<< orphan*/  kfree (struct xfrm_state*) ; 
 int km_query (struct xfrm_state*,struct xfrm_tmpl*,struct xfrm_state*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct xfrm_user_tmpl* nla_data (struct nlattr*) ; 
 struct xfrm_user_acquire* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int verify_newpolicy_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 struct xfrm_state* xfrm_policy_construct (struct net*,int /*<<< orphan*/ *,struct nlattr**,int*) ; 
 struct xfrm_state* xfrm_state_alloc (struct net*) ; 

__attribute__((used)) static int xfrm_add_acquire(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_policy *xp;
	struct xfrm_user_tmpl *ut;
	int i;
	struct nlattr *rt = attrs[XFRMA_TMPL];
	struct xfrm_mark mark;

	struct xfrm_user_acquire *ua = nlmsg_data(nlh);
	struct xfrm_state *x = xfrm_state_alloc(net);
	int err = -ENOMEM;

	if (!x)
		goto nomem;

	xfrm_mark_get(attrs, &mark);

	err = verify_newpolicy_info(&ua->policy);
	if (err)
		goto bad_policy;

	/*   build an XP */
	xp = xfrm_policy_construct(net, &ua->policy, attrs, &err);
	if (!xp)
		goto free_state;

	memcpy(&x->id, &ua->id, sizeof(ua->id));
	memcpy(&x->props.saddr, &ua->saddr, sizeof(ua->saddr));
	memcpy(&x->sel, &ua->sel, sizeof(ua->sel));
	xp->mark.m = x->mark.m = mark.m;
	xp->mark.v = x->mark.v = mark.v;
	ut = nla_data(rt);
	/* extract the templates and for each call km_key */
	for (i = 0; i < xp->xfrm_nr; i++, ut++) {
		struct xfrm_tmpl *t = &xp->xfrm_vec[i];
		memcpy(&x->id, &t->id, sizeof(x->id));
		x->props.mode = t->mode;
		x->props.reqid = t->reqid;
		x->props.family = ut->family;
		t->aalgos = ua->aalgos;
		t->ealgos = ua->ealgos;
		t->calgos = ua->calgos;
		err = km_query(x, t, xp);

	}

	kfree(x);
	kfree(xp);

	return 0;

bad_policy:
	printk("BAD policy passed\n");
free_state:
	kfree(x);
nomem:
	return err;
}