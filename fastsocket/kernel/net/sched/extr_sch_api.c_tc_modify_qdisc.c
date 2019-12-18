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
typedef  scalar_t__ u32 ;
struct tcmsg {scalar_t__ tcm_parent; scalar_t__ tcm_handle; int /*<<< orphan*/  tcm_ifindex; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct net_device {struct netdev_queue rx_queue; struct Qdisc* qdisc; } ;
struct net {int dummy; } ;
struct Qdisc {scalar_t__ handle; struct netdev_queue* dev_queue; TYPE_2__* ops; int /*<<< orphan*/  refcnt; } ;
struct TYPE_4__ {TYPE_1__* cl_ops; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct netdev_queue* (* select_queue ) (struct Qdisc*,struct tcmsg*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ELOOP ; 
 int ENODEV ; 
 int ENOENT ; 
 struct tcmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_H_INGRESS ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_MIN (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ check_loop (struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ ) ; 
 struct net init_net ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qdisc_change (struct Qdisc*,struct nlattr**) ; 
 struct Qdisc* qdisc_create (struct net_device*,struct netdev_queue*,struct Qdisc*,scalar_t__,scalar_t__,struct nlattr**,int*) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 int qdisc_graft (struct net_device*,struct Qdisc*,struct sk_buff*,struct nlmsghdr*,scalar_t__,struct Qdisc*,int /*<<< orphan*/ *) ; 
 struct Qdisc* qdisc_leaf (struct Qdisc*,scalar_t__) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  qdisc_notify (struct sk_buff*,struct nlmsghdr*,scalar_t__,int /*<<< orphan*/ *,struct Qdisc*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 struct netdev_queue* stub1 (struct Qdisc*,struct tcmsg*) ; 

__attribute__((used)) static int tc_modify_qdisc(struct sk_buff *skb, struct nlmsghdr *n, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct tcmsg *tcm;
	struct nlattr *tca[TCA_MAX + 1];
	struct net_device *dev;
	u32 clid;
	struct Qdisc *q, *p;
	int err;

	if (net != &init_net)
		return -EINVAL;

replay:
	/* Reinit, just in case something touches this. */
	tcm = NLMSG_DATA(n);
	clid = tcm->tcm_parent;
	q = p = NULL;

	if ((dev = __dev_get_by_index(&init_net, tcm->tcm_ifindex)) == NULL)
		return -ENODEV;

	err = nlmsg_parse(n, sizeof(*tcm), tca, TCA_MAX, NULL);
	if (err < 0)
		return err;

	if (clid) {
		if (clid != TC_H_ROOT) {
			if (clid != TC_H_INGRESS) {
				if ((p = qdisc_lookup(dev, TC_H_MAJ(clid))) == NULL)
					return -ENOENT;
				q = qdisc_leaf(p, clid);
			} else { /*ingress */
				q = dev->rx_queue.qdisc_sleeping;
			}
		} else {
			q = dev->qdisc;
		}

		/* It may be default qdisc, ignore it */
		if (q && q->handle == 0)
			q = NULL;

		if (!q || !tcm->tcm_handle || q->handle != tcm->tcm_handle) {
			if (tcm->tcm_handle) {
				if (q && !(n->nlmsg_flags&NLM_F_REPLACE))
					return -EEXIST;
				if (TC_H_MIN(tcm->tcm_handle))
					return -EINVAL;
				if ((q = qdisc_lookup(dev, tcm->tcm_handle)) == NULL)
					goto create_n_graft;
				if (n->nlmsg_flags&NLM_F_EXCL)
					return -EEXIST;
				if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], q->ops->id))
					return -EINVAL;
				if (q == p ||
				    (p && check_loop(q, p, 0)))
					return -ELOOP;
				atomic_inc(&q->refcnt);
				goto graft;
			} else {
				if (q == NULL)
					goto create_n_graft;

				/* This magic test requires explanation.
				 *
				 *   We know, that some child q is already
				 *   attached to this parent and have choice:
				 *   either to change it or to create/graft new one.
				 *
				 *   1. We are allowed to create/graft only
				 *   if CREATE and REPLACE flags are set.
				 *
				 *   2. If EXCL is set, requestor wanted to say,
				 *   that qdisc tcm_handle is not expected
				 *   to exist, so that we choose create/graft too.
				 *
				 *   3. The last case is when no flags are set.
				 *   Alas, it is sort of hole in API, we
				 *   cannot decide what to do unambiguously.
				 *   For now we select create/graft, if
				 *   user gave KIND, which does not match existing.
				 */
				if ((n->nlmsg_flags&NLM_F_CREATE) &&
				    (n->nlmsg_flags&NLM_F_REPLACE) &&
				    ((n->nlmsg_flags&NLM_F_EXCL) ||
				     (tca[TCA_KIND] &&
				      nla_strcmp(tca[TCA_KIND], q->ops->id))))
					goto create_n_graft;
			}
		}
	} else {
		if (!tcm->tcm_handle)
			return -EINVAL;
		q = qdisc_lookup(dev, tcm->tcm_handle);
	}

	/* Change qdisc parameters */
	if (q == NULL)
		return -ENOENT;
	if (n->nlmsg_flags&NLM_F_EXCL)
		return -EEXIST;
	if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], q->ops->id))
		return -EINVAL;
	err = qdisc_change(q, tca);
	if (err == 0)
		qdisc_notify(skb, n, clid, NULL, q);
	return err;

create_n_graft:
	if (!(n->nlmsg_flags&NLM_F_CREATE))
		return -ENOENT;
	if (clid == TC_H_INGRESS)
		q = qdisc_create(dev, &dev->rx_queue, p,
				 tcm->tcm_parent, tcm->tcm_parent,
				 tca, &err);
	else {
		struct netdev_queue *dev_queue;

		if (p && p->ops->cl_ops && p->ops->cl_ops->select_queue)
			dev_queue = p->ops->cl_ops->select_queue(p, tcm);
		else if (p)
			dev_queue = p->dev_queue;
		else
			dev_queue = netdev_get_tx_queue(dev, 0);

		q = qdisc_create(dev, dev_queue, p,
				 tcm->tcm_parent, tcm->tcm_handle,
				 tca, &err);
	}
	if (q == NULL) {
		if (err == -EAGAIN)
			goto replay;
		return err;
	}

graft:
	err = qdisc_graft(dev, p, skb, n, clid, q, NULL);
	if (err) {
		if (q)
			qdisc_destroy(q);
		return err;
	}

	return 0;
}