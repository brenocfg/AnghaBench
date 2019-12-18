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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ dev; } ;
struct TYPE_5__ {scalar_t__ high_thresh; int /*<<< orphan*/  mem; } ;
struct TYPE_6__ {TYPE_1__ frags; } ;
struct net {TYPE_2__ ipv4; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct ipq {TYPE_3__ q; } ;
struct TYPE_8__ {scalar_t__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMREQDS ; 
 int /*<<< orphan*/  IP_INC_STATS_BH (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct net* dev_net (scalar_t__) ; 
 int /*<<< orphan*/  ip_evictor (struct net*) ; 
 struct ipq* ip_find (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ip_frag_queue (struct ipq*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipq_put (struct ipq*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_4__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ip_defrag(struct sk_buff *skb, u32 user)
{
	struct ipq *qp;
	struct net *net;

	net = skb->dev ? dev_net(skb->dev) : dev_net(skb_dst(skb)->dev);
	IP_INC_STATS_BH(net, IPSTATS_MIB_REASMREQDS);

	/* Start by cleaning up the memory. */
	if (atomic_read(&net->ipv4.frags.mem) > net->ipv4.frags.high_thresh)
		ip_evictor(net);

	/* Lookup (or create) queue header */
	if ((qp = ip_find(net, ip_hdr(skb), user)) != NULL) {
		int ret;

		spin_lock(&qp->q.lock);

		ret = ip_frag_queue(qp, skb);

		spin_unlock(&qp->q.lock);
		ipq_put(qp);
		return ret;
	}

	IP_INC_STATS_BH(net, IPSTATS_MIB_REASMFAILS);
	kfree_skb(skb);
	return -ENOMEM;
}