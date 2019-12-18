#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet_frags {int dummy; } ;
struct TYPE_4__ {int last_in; int /*<<< orphan*/  lock; TYPE_3__* fragments; } ;
struct frag_queue {TYPE_1__ q; int /*<<< orphan*/  iif; } ;
struct TYPE_5__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_EXC_FRAGTIME ; 
 int /*<<< orphan*/  ICMPV6_TIME_EXCEED ; 
 int INET_FRAG_COMPLETE ; 
 int INET_FRAG_FIRST_IN ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMTIMEOUT ; 
 int /*<<< orphan*/  __in6_dev_get (struct net_device*) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  icmpv6_send (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  inet_frag_kill (TYPE_1__*,struct inet_frags*) ; 
 int /*<<< orphan*/  inet_frag_put (TYPE_1__*,struct inet_frags*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ip6_expire_frag_queue(struct net *net, struct frag_queue *fq,
			   struct inet_frags *frags)
{
	struct net_device *dev = NULL;

	spin_lock(&fq->q.lock);

	if (fq->q.last_in & INET_FRAG_COMPLETE)
		goto out;

	inet_frag_kill(&fq->q, frags);

	dev = dev_get_by_index(net, fq->iif);
	if (!dev)
		goto out;

	rcu_read_lock();
	IP6_INC_STATS_BH(net, __in6_dev_get(dev), IPSTATS_MIB_REASMTIMEOUT);
	IP6_INC_STATS_BH(net, __in6_dev_get(dev), IPSTATS_MIB_REASMFAILS);
	rcu_read_unlock();

	/* Don't send error if the first segment did not arrive. */
	if (!(fq->q.last_in & INET_FRAG_FIRST_IN) || !fq->q.fragments)
		goto out;

	/*
	   But use as source device on which LAST ARRIVED
	   segment was received. And do not use fq->dev
	   pointer directly, device might already disappeared.
	 */
	fq->q.fragments->dev = dev;
	icmpv6_send(fq->q.fragments, ICMPV6_TIME_EXCEED, ICMPV6_EXC_FRAGTIME, 0, dev);
out:
	if (dev)
		dev_put(dev);
	spin_unlock(&fq->q.lock);
	inet_frag_put(&fq->q, frags);
}