#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ipoib_neigh_table {int /*<<< orphan*/  entries; int /*<<< orphan*/  htbl; } ;
struct ipoib_neigh_hash {int /*<<< orphan*/ * buckets; int /*<<< orphan*/  hnext; void* alive; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  daddr; } ;
struct ipoib_neigh {int /*<<< orphan*/ * buckets; int /*<<< orphan*/  hnext; void* alive; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  daddr; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; struct ipoib_neigh_table ntbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 size_t ipoib_addr_hash (struct ipoib_neigh_hash*,int /*<<< orphan*/ *) ; 
 struct ipoib_neigh_hash* ipoib_neigh_ctor (int /*<<< orphan*/ *,struct net_device*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ipoib_neigh_hash*) ; 
 struct ipoib_neigh_hash* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ipoib_neigh *ipoib_neigh_alloc(u8 *daddr,
				      struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_neigh_table *ntbl = &priv->ntbl;
	struct ipoib_neigh_hash *htbl;
	struct ipoib_neigh *neigh;
	u32 hash_val;

	htbl = rcu_dereference_protected(ntbl->htbl,
					 lockdep_is_held(&priv->lock));
	if (!htbl) {
		neigh = NULL;
		goto out_unlock;
	}

	/* need to add a new neigh, but maybe some other thread succeeded?
	 * recalc hash, maybe hash resize took place so we do a search
	 */
	hash_val = ipoib_addr_hash(htbl, daddr);
	for (neigh = rcu_dereference_protected(htbl->buckets[hash_val],
					       lockdep_is_held(&priv->lock));
	     neigh != NULL;
	     neigh = rcu_dereference_protected(neigh->hnext,
					       lockdep_is_held(&priv->lock))) {
		if (memcmp(daddr, neigh->daddr, INFINIBAND_ALEN) == 0) {
			/* found, take one ref on behalf of the caller */
			if (!atomic_inc_not_zero(&neigh->refcnt)) {
				/* deleted */
				neigh = NULL;
				break;
			}
			neigh->alive = jiffies;
			goto out_unlock;
		}
	}

	neigh = ipoib_neigh_ctor(daddr, dev);
	if (!neigh)
		goto out_unlock;

	/* one ref on behalf of the hash table */
	atomic_inc(&neigh->refcnt);
	neigh->alive = jiffies;
	/* put in hash */
	rcu_assign_pointer(neigh->hnext,
			   rcu_dereference_protected(htbl->buckets[hash_val],
						     lockdep_is_held(&priv->lock)));
	rcu_assign_pointer(htbl->buckets[hash_val], neigh);
	atomic_inc(&ntbl->entries);

out_unlock:

	return neigh;
}