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
struct net_bridge_mdb_htable {int max; int ver; int /*<<< orphan*/  rcu; struct net_bridge_mdb_htable* mhash; int /*<<< orphan*/  secret; int /*<<< orphan*/  size; struct net_bridge_mdb_htable* old; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int br_mdb_copy (struct net_bridge_mdb_htable*,struct net_bridge_mdb_htable*,int) ; 
 int /*<<< orphan*/  br_mdb_free ; 
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct net_bridge_mdb_htable*) ; 
 struct net_bridge_mdb_htable* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct net_bridge_mdb_htable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct net_bridge_mdb_htable*,struct net_bridge_mdb_htable*) ; 

__attribute__((used)) static int br_mdb_rehash(struct net_bridge_mdb_htable **mdbp, int max,
			 int elasticity)
{
	struct net_bridge_mdb_htable *old = *mdbp;
	struct net_bridge_mdb_htable *mdb;
	int err;

	mdb = kmalloc(sizeof(*mdb), GFP_ATOMIC);
	if (!mdb)
		return -ENOMEM;

	mdb->max = max;
	mdb->old = old;

	mdb->mhash = kzalloc(max * sizeof(*mdb->mhash), GFP_ATOMIC);
	if (!mdb->mhash) {
		kfree(mdb);
		return -ENOMEM;
	}

	mdb->size = old ? old->size : 0;
	mdb->ver = old ? old->ver ^ 1 : 0;

	if (!old || elasticity)
		get_random_bytes(&mdb->secret, sizeof(mdb->secret));
	else
		mdb->secret = old->secret;

	if (!old)
		goto out;

	err = br_mdb_copy(mdb, old, elasticity);
	if (err) {
		kfree(mdb->mhash);
		kfree(mdb);
		return err;
	}

	call_rcu_bh(&mdb->rcu, br_mdb_free);

out:
	rcu_assign_pointer(*mdbp, mdb);

	return 0;
}