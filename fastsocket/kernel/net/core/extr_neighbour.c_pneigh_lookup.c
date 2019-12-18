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
struct pneigh_entry {struct pneigh_entry* next; struct net_device* dev; int /*<<< orphan*/  key; int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct neigh_table {int key_len; int /*<<< orphan*/  lock; struct pneigh_entry** phash_buckets; scalar_t__ (* pconstructor ) (struct pneigh_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pneigh_entry* __pneigh_lookup_1 (struct pneigh_entry*,struct net*,void const*,int,struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  hold_net (struct net*) ; 
 int /*<<< orphan*/  kfree (struct pneigh_entry*) ; 
 struct pneigh_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 size_t pneigh_hash (void const*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_net (struct net*) ; 
 scalar_t__ stub1 (struct pneigh_entry*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct pneigh_entry * pneigh_lookup(struct neigh_table *tbl,
				    struct net *net, const void *pkey,
				    struct net_device *dev, int creat)
{
	struct pneigh_entry *n;
	int key_len = tbl->key_len;
	u32 hash_val = pneigh_hash(pkey, key_len);

	read_lock_bh(&tbl->lock);
	n = __pneigh_lookup_1(tbl->phash_buckets[hash_val],
			      net, pkey, key_len, dev);
	read_unlock_bh(&tbl->lock);

	if (n || !creat)
		goto out;

	ASSERT_RTNL();

	n = kmalloc(sizeof(*n) + key_len, GFP_KERNEL);
	if (!n)
		goto out;

	write_pnet(&n->net, hold_net(net));
	memcpy(n->key, pkey, key_len);
	n->dev = dev;
	if (dev)
		dev_hold(dev);

	if (tbl->pconstructor && tbl->pconstructor(n)) {
		if (dev)
			dev_put(dev);
		release_net(net);
		kfree(n);
		n = NULL;
		goto out;
	}

	write_lock_bh(&tbl->lock);
	n->next = tbl->phash_buckets[hash_val];
	tbl->phash_buckets[hash_val] = n;
	write_unlock_bh(&tbl->lock);
out:
	return n;
}