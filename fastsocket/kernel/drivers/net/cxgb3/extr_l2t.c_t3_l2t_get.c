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
struct t3cdev {int dummy; } ;
struct port_info {int port_id; } ;
struct net_device {int ifindex; int priv_flags; } ;
struct neighbour {struct net_device* dev; scalar_t__ primary_key; } ;
struct l2t_entry {scalar_t__ addr; int ifindex; int smt_idx; int /*<<< orphan*/  lock; int /*<<< orphan*/  vlan; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  state; struct l2t_entry* next; } ;
struct l2t_data {int /*<<< orphan*/  lock; TYPE_1__* l2tab; } ;
struct dst_entry {struct neighbour* neighbour; } ;
struct TYPE_2__ {struct l2t_entry* first; } ;

/* Variables and functions */
 int IFF_802_1Q_VLAN ; 
 struct l2t_data* L2DATA (struct t3cdev*) ; 
 int /*<<< orphan*/  L2T_STATE_RESOLVING ; 
 int /*<<< orphan*/  VLAN_NONE ; 
 struct l2t_entry* alloc_l2e (struct l2t_data*) ; 
 int arp_hash (scalar_t__,int,struct l2t_data*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  l2t_hold (struct l2t_data*,struct l2t_entry*) ; 
 int /*<<< orphan*/  neigh_replace (struct l2t_entry*,struct neighbour*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  reuse_entry (struct l2t_entry*,struct neighbour*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct l2t_entry *t3_l2t_get(struct t3cdev *cdev, struct dst_entry *dst,
			     struct net_device *dev)
{
	struct l2t_entry *e = NULL;
	struct neighbour *neigh;
	struct port_info *p;
	struct l2t_data *d;
	int hash;
	u32 addr;
	int ifidx;
	int smt_idx;

	rcu_read_lock();
	neigh = dst->neighbour;
	if (!neigh)
		goto done_rcu;

	addr = *(u32 *) neigh->primary_key;
	ifidx = neigh->dev->ifindex;

	if (!dev)
		dev = neigh->dev;
	p = netdev_priv(dev);
	smt_idx = p->port_id;

	d = L2DATA(cdev);
	if (!d)
		goto done_rcu;

	hash = arp_hash(addr, ifidx, d);

	write_lock_bh(&d->lock);
	for (e = d->l2tab[hash].first; e; e = e->next)
		if (e->addr == addr && e->ifindex == ifidx &&
		    e->smt_idx == smt_idx) {
			l2t_hold(d, e);
			if (atomic_read(&e->refcnt) == 1)
				reuse_entry(e, neigh);
			goto done_unlock;
		}

	/* Need to allocate a new entry */
	e = alloc_l2e(d);
	if (e) {
		spin_lock(&e->lock);	/* avoid race with t3_l2t_free */
		e->next = d->l2tab[hash].first;
		d->l2tab[hash].first = e;
		e->state = L2T_STATE_RESOLVING;
		e->addr = addr;
		e->ifindex = ifidx;
		e->smt_idx = smt_idx;
		atomic_set(&e->refcnt, 1);
		neigh_replace(e, neigh);
		if (neigh->dev->priv_flags & IFF_802_1Q_VLAN)
			e->vlan = vlan_dev_vlan_id(neigh->dev);
		else
			e->vlan = VLAN_NONE;
		spin_unlock(&e->lock);
	}
done_unlock:
	write_unlock_bh(&d->lock);
done_rcu:
	rcu_read_unlock();
	return e;
}