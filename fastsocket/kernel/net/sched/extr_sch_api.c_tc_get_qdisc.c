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
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {struct Qdisc* qdisc_sleeping; } ;
struct net_device {struct Qdisc* qdisc; TYPE_1__ rx_queue; } ;
struct net {int dummy; } ;
struct Qdisc {scalar_t__ handle; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 struct tcmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 scalar_t__ RTM_DELQDISC ; 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_H_INGRESS ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct net init_net ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qdisc_graft (struct net_device*,struct Qdisc*,struct sk_buff*,struct nlmsghdr*,scalar_t__,int /*<<< orphan*/ *,struct Qdisc*) ; 
 struct Qdisc* qdisc_leaf (struct Qdisc*,scalar_t__) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  qdisc_notify (struct sk_buff*,struct nlmsghdr*,scalar_t__,int /*<<< orphan*/ *,struct Qdisc*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_get_qdisc(struct sk_buff *skb, struct nlmsghdr *n, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct tcmsg *tcm = NLMSG_DATA(n);
	struct nlattr *tca[TCA_MAX + 1];
	struct net_device *dev;
	u32 clid = tcm->tcm_parent;
	struct Qdisc *q = NULL;
	struct Qdisc *p = NULL;
	int err;

	if (net != &init_net)
		return -EINVAL;

	if ((dev = __dev_get_by_index(&init_net, tcm->tcm_ifindex)) == NULL)
		return -ENODEV;

	err = nlmsg_parse(n, sizeof(*tcm), tca, TCA_MAX, NULL);
	if (err < 0)
		return err;

	if (clid) {
		if (clid != TC_H_ROOT) {
			if (TC_H_MAJ(clid) != TC_H_MAJ(TC_H_INGRESS)) {
				if ((p = qdisc_lookup(dev, TC_H_MAJ(clid))) == NULL)
					return -ENOENT;
				q = qdisc_leaf(p, clid);
			} else { /* ingress */
				q = dev->rx_queue.qdisc_sleeping;
			}
		} else {
			q = dev->qdisc;
		}
		if (!q)
			return -ENOENT;

		if (tcm->tcm_handle && q->handle != tcm->tcm_handle)
			return -EINVAL;
	} else {
		if ((q = qdisc_lookup(dev, tcm->tcm_handle)) == NULL)
			return -ENOENT;
	}

	if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], q->ops->id))
		return -EINVAL;

	if (n->nlmsg_type == RTM_DELQDISC) {
		if (!clid)
			return -EINVAL;
		if (q->handle == 0)
			return -ENOENT;
		if ((err = qdisc_graft(dev, p, skb, n, clid, NULL, q)) != 0)
			return err;
	} else {
		qdisc_notify(skb, n, clid, NULL, q);
	}
	return 0;
}