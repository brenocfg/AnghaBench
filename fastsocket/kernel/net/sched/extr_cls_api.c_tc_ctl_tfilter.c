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
typedef  scalar_t__ u32 ;
struct tcmsg {scalar_t__ tcm_info; scalar_t__ tcm_parent; scalar_t__ tcm_handle; int /*<<< orphan*/  tcm_ifindex; } ;
struct tcf_proto_ops {int (* init ) (struct tcf_proto*) ;unsigned long (* get ) (struct tcf_proto*,scalar_t__) ;int (* delete ) (struct tcf_proto*,unsigned long) ;int (* change ) (struct tcf_proto*,unsigned long,scalar_t__,struct nlattr**,unsigned long*) ;int /*<<< orphan*/  kind; int /*<<< orphan*/  owner; int /*<<< orphan*/  classify; } ;
struct tcf_proto {scalar_t__ prio; scalar_t__ protocol; struct tcf_proto* next; struct tcf_proto_ops* ops; scalar_t__ classid; int /*<<< orphan*/  classify; struct Qdisc* q; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct net_device {struct Qdisc* qdisc; } ;
struct net {int dummy; } ;
struct Qdisc_class_ops {unsigned long (* get ) (struct Qdisc*,scalar_t__) ;int /*<<< orphan*/  (* put ) (struct Qdisc*,unsigned long) ;struct tcf_proto** (* tcf_chain ) (struct Qdisc*,unsigned long) ;} ;
struct Qdisc {scalar_t__ handle; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFNAMSIZ ; 
 struct tcmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
#define  RTM_DELTFILTER 130 
#define  RTM_GETTFILTER 129 
#define  RTM_NEWTFILTER 128 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_MAKE (int,unsigned int) ; 
 scalar_t__ TC_H_MIN (scalar_t__) ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct net init_net ; 
 int /*<<< orphan*/  kfree (struct tcf_proto*) ; 
 struct tcf_proto* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 int nla_strlcpy (char*,struct nlattr*,int) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/ * qdisc_root_sleeping_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned long stub1 (struct Qdisc*,scalar_t__) ; 
 struct tcf_proto** stub2 (struct Qdisc*,unsigned long) ; 
 int stub3 (struct tcf_proto*) ; 
 unsigned long stub4 (struct tcf_proto*,scalar_t__) ; 
 int stub5 (struct tcf_proto*,unsigned long) ; 
 int stub6 (struct tcf_proto*,unsigned long,scalar_t__,struct nlattr**,unsigned long*) ; 
 int /*<<< orphan*/  stub7 (struct Qdisc*,unsigned long) ; 
 scalar_t__ tcf_auto_prio (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_destroy (struct tcf_proto*) ; 
 struct tcf_proto_ops* tcf_proto_lookup_ops (struct nlattr*) ; 
 int tfilter_notify (struct sk_buff*,struct nlmsghdr*,struct tcf_proto*,unsigned long,int const) ; 

__attribute__((used)) static int tc_ctl_tfilter(struct sk_buff *skb, struct nlmsghdr *n, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_MAX + 1];
	spinlock_t *root_lock;
	struct tcmsg *t;
	u32 protocol;
	u32 prio;
	u32 nprio;
	u32 parent;
	struct net_device *dev;
	struct Qdisc  *q;
	struct tcf_proto **back, **chain;
	struct tcf_proto *tp;
	struct tcf_proto_ops *tp_ops;
	const struct Qdisc_class_ops *cops;
	unsigned long cl;
	unsigned long fh;
	int err;
	int tp_created = 0;

	if (net != &init_net)
		return -EINVAL;

replay:
	t = NLMSG_DATA(n);
	protocol = TC_H_MIN(t->tcm_info);
	prio = TC_H_MAJ(t->tcm_info);
	nprio = prio;
	parent = t->tcm_parent;
	cl = 0;

	if (prio == 0) {
		/* If no priority is given, user wants we allocated it. */
		if (n->nlmsg_type != RTM_NEWTFILTER || !(n->nlmsg_flags&NLM_F_CREATE))
			return -ENOENT;
		prio = TC_H_MAKE(0x80000000U, 0U);
	}

	/* Find head of filter chain. */

	/* Find link */
	dev = __dev_get_by_index(&init_net, t->tcm_ifindex);
	if (dev == NULL)
		return -ENODEV;

	err = nlmsg_parse(n, sizeof(*t), tca, TCA_MAX, NULL);
	if (err < 0)
		return err;

	/* Find qdisc */
	if (!parent) {
		q = dev->qdisc;
		parent = q->handle;
	} else {
		q = qdisc_lookup(dev, TC_H_MAJ(t->tcm_parent));
		if (q == NULL)
			return -EINVAL;
	}

	/* Is it classful? */
	if ((cops = q->ops->cl_ops) == NULL)
		return -EINVAL;

	if (cops->tcf_chain == NULL)
		return -EOPNOTSUPP;

	/* Do we search for filter, attached to class? */
	if (TC_H_MIN(parent)) {
		cl = cops->get(q, parent);
		if (cl == 0)
			return -ENOENT;
	}

	/* And the last stroke */
	chain = cops->tcf_chain(q, cl);
	err = -EINVAL;
	if (chain == NULL)
		goto errout;

	/* Check the chain for existence of proto-tcf with this priority */
	for (back = chain; (tp=*back) != NULL; back = &tp->next) {
		if (tp->prio >= prio) {
			if (tp->prio == prio) {
				if (!nprio || (tp->protocol != protocol && protocol))
					goto errout;
			} else
				tp = NULL;
			break;
		}
	}

	root_lock = qdisc_root_sleeping_lock(q);

	if (tp == NULL) {
		/* Proto-tcf does not exist, create new one */

		if (tca[TCA_KIND] == NULL || !protocol)
			goto errout;

		err = -ENOENT;
		if (n->nlmsg_type != RTM_NEWTFILTER || !(n->nlmsg_flags&NLM_F_CREATE))
			goto errout;


		/* Create new proto tcf */

		err = -ENOBUFS;
		tp = kzalloc(sizeof(*tp), GFP_KERNEL);
		if (tp == NULL)
			goto errout;
		err = -ENOENT;
		tp_ops = tcf_proto_lookup_ops(tca[TCA_KIND]);
		if (tp_ops == NULL) {
#ifdef CONFIG_MODULES
			struct nlattr *kind = tca[TCA_KIND];
			char name[IFNAMSIZ];

			if (kind != NULL &&
			    nla_strlcpy(name, kind, IFNAMSIZ) < IFNAMSIZ) {
				rtnl_unlock();
				request_module("cls_%s", name);
				rtnl_lock();
				tp_ops = tcf_proto_lookup_ops(kind);
				/* We dropped the RTNL semaphore in order to
				 * perform the module load.  So, even if we
				 * succeeded in loading the module we have to
				 * replay the request.  We indicate this using
				 * -EAGAIN.
				 */
				if (tp_ops != NULL) {
					module_put(tp_ops->owner);
					err = -EAGAIN;
				}
			}
#endif
			kfree(tp);
			goto errout;
		}
		tp->ops = tp_ops;
		tp->protocol = protocol;
		tp->prio = nprio ? : TC_H_MAJ(tcf_auto_prio(*back));
		tp->q = q;
		tp->classify = tp_ops->classify;
		tp->classid = parent;

		err = tp_ops->init(tp);
		if (err != 0) {
			module_put(tp_ops->owner);
			kfree(tp);
			goto errout;
		}

		tp_created = 1;

	} else if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], tp->ops->kind))
		goto errout;

	fh = tp->ops->get(tp, t->tcm_handle);

	if (fh == 0) {
		if (n->nlmsg_type == RTM_DELTFILTER && t->tcm_handle == 0) {
			spin_lock_bh(root_lock);
			*back = tp->next;
			spin_unlock_bh(root_lock);

			tfilter_notify(skb, n, tp, fh, RTM_DELTFILTER);
			tcf_destroy(tp);
			err = 0;
			goto errout;
		}

		err = -ENOENT;
		if (n->nlmsg_type != RTM_NEWTFILTER ||
		    !(n->nlmsg_flags & NLM_F_CREATE))
			goto errout;
	} else {
		switch (n->nlmsg_type) {
		case RTM_NEWTFILTER:
			err = -EEXIST;
			if (n->nlmsg_flags & NLM_F_EXCL) {
				if (tp_created)
					tcf_destroy(tp);
				goto errout;
			}
			break;
		case RTM_DELTFILTER:
			err = tp->ops->delete(tp, fh);
			if (err == 0)
				tfilter_notify(skb, n, tp, fh, RTM_DELTFILTER);
			goto errout;
		case RTM_GETTFILTER:
			err = tfilter_notify(skb, n, tp, fh, RTM_NEWTFILTER);
			goto errout;
		default:
			err = -EINVAL;
			goto errout;
		}
	}

	err = tp->ops->change(tp, cl, t->tcm_handle, tca, &fh);
	if (err == 0) {
		if (tp_created) {
			spin_lock_bh(root_lock);
			tp->next = *back;
			*back = tp;
			spin_unlock_bh(root_lock);
		}
		tfilter_notify(skb, n, tp, fh, RTM_NEWTFILTER);
	} else {
		if (tp_created)
			tcf_destroy(tp);
	}

errout:
	if (cl)
		cops->put(q, cl);
	if (err == -EAGAIN)
		/* Replay the request. */
		goto replay;
	return err;
}