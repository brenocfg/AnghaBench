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
struct tcmsg {int /*<<< orphan*/  tcm_ifindex; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; } ;
struct netdev_queue {int /*<<< orphan*/  qdisc_sleeping; } ;
struct net_device {struct netdev_queue rx_queue; int /*<<< orphan*/  qdisc; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ nlmsg_len; } ;

/* Variables and functions */
 scalar_t__ NLMSG_DATA (TYPE_1__*) ; 
 scalar_t__ NLMSG_LENGTH (int) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net init_net ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 scalar_t__ tc_dump_tclass_root (int /*<<< orphan*/ ,struct sk_buff*,struct tcmsg*,struct netlink_callback*,int*,int) ; 

__attribute__((used)) static int tc_dump_tclass(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct tcmsg *tcm = (struct tcmsg*)NLMSG_DATA(cb->nlh);
	struct net *net = sock_net(skb->sk);
	struct netdev_queue *dev_queue;
	struct net_device *dev;
	int t, s_t;

	if (net != &init_net)
		return 0;

	if (cb->nlh->nlmsg_len < NLMSG_LENGTH(sizeof(*tcm)))
		return 0;
	if ((dev = dev_get_by_index(&init_net, tcm->tcm_ifindex)) == NULL)
		return 0;

	s_t = cb->args[0];
	t = 0;

	if (tc_dump_tclass_root(dev->qdisc, skb, tcm, cb, &t, s_t) < 0)
		goto done;

	dev_queue = &dev->rx_queue;
	if (tc_dump_tclass_root(dev_queue->qdisc_sleeping, skb, tcm, cb, &t, s_t) < 0)
		goto done;

done:
	cb->args[0] = t;

	dev_put(dev);
	return skb->len;
}