#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcmsg {int /*<<< orphan*/  tcm_info; int /*<<< orphan*/  tcm_parent; int /*<<< orphan*/  tcm_ifindex; } ;
struct tcf_proto {scalar_t__ prio; scalar_t__ protocol; TYPE_2__* ops; struct tcf_proto* next; } ;
struct TYPE_8__ {int skip; int count; scalar_t__ stop; int /*<<< orphan*/  fn; } ;
struct tcf_dump_args {TYPE_3__ w; struct netlink_callback* cb; struct sk_buff* skb; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_4__* nlh; int /*<<< orphan*/  skb; } ;
struct net_device {struct Qdisc* qdisc; } ;
struct net {int dummy; } ;
struct Qdisc_class_ops {unsigned long (* get ) (struct Qdisc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* put ) (struct Qdisc*,unsigned long) ;struct tcf_proto** (* tcf_chain ) (struct Qdisc*,unsigned long) ;} ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  pid; } ;
struct TYPE_9__ {scalar_t__ nlmsg_len; int /*<<< orphan*/  nlmsg_seq; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* walk ) (struct tcf_proto*,TYPE_3__*) ;} ;
struct TYPE_6__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 TYPE_5__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 scalar_t__ NLMSG_DATA (TYPE_4__*) ; 
 scalar_t__ NLMSG_LENGTH (int) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWTFILTER ; 
 scalar_t__ TC_H_MAJ (int /*<<< orphan*/ ) ; 
 scalar_t__ TC_H_MIN (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net init_net ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,scalar_t__) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct Qdisc*,int /*<<< orphan*/ ) ; 
 struct tcf_proto** stub2 (struct Qdisc*,unsigned long) ; 
 int /*<<< orphan*/  stub3 (struct tcf_proto*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (struct Qdisc*,unsigned long) ; 
 scalar_t__ tcf_fill_node (struct sk_buff*,struct tcf_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_node_dump ; 

__attribute__((used)) static int tc_dump_tfilter(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	int t;
	int s_t;
	struct net_device *dev;
	struct Qdisc *q;
	struct tcf_proto *tp, **chain;
	struct tcmsg *tcm = (struct tcmsg *)NLMSG_DATA(cb->nlh);
	unsigned long cl = 0;
	const struct Qdisc_class_ops *cops;
	struct tcf_dump_args arg;

	if (net != &init_net)
		return 0;

	if (cb->nlh->nlmsg_len < NLMSG_LENGTH(sizeof(*tcm)))
		return skb->len;
	if ((dev = dev_get_by_index(&init_net, tcm->tcm_ifindex)) == NULL)
		return skb->len;

	if (!tcm->tcm_parent)
		q = dev->qdisc;
	else
		q = qdisc_lookup(dev, TC_H_MAJ(tcm->tcm_parent));
	if (!q)
		goto out;
	if ((cops = q->ops->cl_ops) == NULL)
		goto errout;
	if (cops->tcf_chain == NULL)
		goto errout;
	if (TC_H_MIN(tcm->tcm_parent)) {
		cl = cops->get(q, tcm->tcm_parent);
		if (cl == 0)
			goto errout;
	}
	chain = cops->tcf_chain(q, cl);
	if (chain == NULL)
		goto errout;

	s_t = cb->args[0];

	for (tp=*chain, t=0; tp; tp = tp->next, t++) {
		if (t < s_t) continue;
		if (TC_H_MAJ(tcm->tcm_info) &&
		    TC_H_MAJ(tcm->tcm_info) != tp->prio)
			continue;
		if (TC_H_MIN(tcm->tcm_info) &&
		    TC_H_MIN(tcm->tcm_info) != tp->protocol)
			continue;
		if (t > s_t)
			memset(&cb->args[1], 0, sizeof(cb->args)-sizeof(cb->args[0]));
		if (cb->args[1] == 0) {
			if (tcf_fill_node(skb, tp, 0, NETLINK_CB(cb->skb).pid,
					  cb->nlh->nlmsg_seq, NLM_F_MULTI,
					  RTM_NEWTFILTER) <= 0)
				break;

			cb->args[1] = 1;
		}
		if (tp->ops->walk == NULL)
			continue;
		arg.w.fn = tcf_node_dump;
		arg.skb = skb;
		arg.cb = cb;
		arg.w.stop = 0;
		arg.w.skip = cb->args[1]-1;
		arg.w.count = 0;
		tp->ops->walk(tp, &arg.w);
		cb->args[1] = arg.w.count+1;
		if (arg.w.stop)
			break;
	}

	cb->args[0] = t;

errout:
	if (cl)
		cops->put(q, cl);
out:
	dev_put(dev);
	return skb->len;
}