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
typedef  size_t u32 ;
struct net {int dummy; } ;
struct neighbour {int /*<<< orphan*/  dev; int /*<<< orphan*/  primary_key; struct neighbour* next; } ;
struct neigh_table {int key_len; size_t (* hash ) (void const*,int /*<<< orphan*/ *) ;size_t hash_mask; int /*<<< orphan*/  lock; struct neighbour** hash_buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hits ; 
 int /*<<< orphan*/  lookups ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  neigh_hold (struct neighbour*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 size_t stub1 (void const*,int /*<<< orphan*/ *) ; 

struct neighbour *neigh_lookup_nodev(struct neigh_table *tbl, struct net *net,
				     const void *pkey)
{
	struct neighbour *n;
	int key_len = tbl->key_len;
	u32 hash_val;

	NEIGH_CACHE_STAT_INC(tbl, lookups);

	read_lock_bh(&tbl->lock);
	hash_val = tbl->hash(pkey, NULL);
	for (n = tbl->hash_buckets[hash_val & tbl->hash_mask]; n; n = n->next) {
		if (!memcmp(n->primary_key, pkey, key_len) &&
		    net_eq(dev_net(n->dev), net)) {
			neigh_hold(n);
			NEIGH_CACHE_STAT_INC(tbl, hits);
			break;
		}
	}
	read_unlock_bh(&tbl->lock);
	return n;
}