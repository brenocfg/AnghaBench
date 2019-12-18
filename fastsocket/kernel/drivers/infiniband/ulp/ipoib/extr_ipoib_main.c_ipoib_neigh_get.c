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
struct ipoib_neigh_table {int /*<<< orphan*/  htbl; } ;
struct ipoib_neigh_hash {int /*<<< orphan*/ * buckets; } ;
struct ipoib_neigh {int /*<<< orphan*/  alive; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  daddr; int /*<<< orphan*/  hnext; } ;
struct ipoib_dev_priv {struct ipoib_neigh_table ntbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 size_t ipoib_addr_hash (struct ipoib_neigh_hash*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 void* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

struct ipoib_neigh *ipoib_neigh_get(struct net_device *dev, u8 *daddr)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_neigh_table *ntbl = &priv->ntbl;
	struct ipoib_neigh_hash *htbl;
	struct ipoib_neigh *neigh = NULL;
	u32 hash_val;

	rcu_read_lock_bh();

	htbl = rcu_dereference_bh(ntbl->htbl);

	if (!htbl)
		goto out_unlock;

	hash_val = ipoib_addr_hash(htbl, daddr);
	for (neigh = rcu_dereference_bh(htbl->buckets[hash_val]);
	     neigh != NULL;
	     neigh = rcu_dereference_bh(neigh->hnext)) {
		if (memcmp(daddr, neigh->daddr, INFINIBAND_ALEN) == 0) {
			/* found, take one ref on behalf of the caller */
			if (!atomic_inc_not_zero(&neigh->refcnt)) {
				/* deleted */
				neigh = NULL;
				goto out_unlock;
			}
			neigh->alive = jiffies;
			goto out_unlock;
		}
	}

out_unlock:
	rcu_read_unlock_bh();
	return neigh;
}