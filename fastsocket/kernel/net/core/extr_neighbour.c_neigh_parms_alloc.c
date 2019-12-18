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
struct net_device_ops {scalar_t__ (* ndo_neigh_setup ) (struct net_device*,struct neigh_parms*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct neigh_parms* next; } ;
struct neigh_table {int /*<<< orphan*/  lock; TYPE_1__ parms; } ;
struct neigh_parms {struct neigh_parms* next; int /*<<< orphan*/ * sysctl_table; int /*<<< orphan*/  net; struct net_device* dev; int /*<<< orphan*/  base_reachable_time; int /*<<< orphan*/  reachable_time; int /*<<< orphan*/  refcnt; struct neigh_table* tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  hold_net (struct net*) ; 
 int /*<<< orphan*/  kfree (struct neigh_parms*) ; 
 struct neigh_parms* kmemdup (struct neigh_parms*,int,int /*<<< orphan*/ ) ; 
 struct neigh_parms* lookup_neigh_parms (struct neigh_table*,struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_rand_reach_time (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct net_device*,struct neigh_parms*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct neigh_parms *neigh_parms_alloc(struct net_device *dev,
				      struct neigh_table *tbl)
{
	struct neigh_parms *p, *ref;
	struct net *net = dev_net(dev);
	const struct net_device_ops *ops = dev->netdev_ops;

	ref = lookup_neigh_parms(tbl, net, 0);
	if (!ref)
		return NULL;

	p = kmemdup(ref, sizeof(*p), GFP_KERNEL);
	if (p) {
		p->tbl		  = tbl;
		atomic_set(&p->refcnt, 1);
		p->reachable_time =
				neigh_rand_reach_time(p->base_reachable_time);

		if (ops->ndo_neigh_setup && ops->ndo_neigh_setup(dev, p)) {
			kfree(p);
			return NULL;
		}

		dev_hold(dev);
		p->dev = dev;
		write_pnet(&p->net, hold_net(net));
		p->sysctl_table = NULL;
		write_lock_bh(&tbl->lock);
		p->next		= tbl->parms.next;
		tbl->parms.next = p;
		write_unlock_bh(&tbl->lock);
	}
	return p;
}