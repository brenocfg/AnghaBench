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
typedef  unsigned long u32 ;
struct net_bridge {unsigned long hash_max; int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  hash_elasticity; TYPE_1__* mdb; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned long size; scalar_t__ old; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int br_mdb_rehash (TYPE_1__**,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int br_multicast_set_hash_max(struct net_bridge *br, unsigned long val)
{
	int err = -ENOENT;
	u32 old;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev))
		goto unlock;

	err = -EINVAL;
	if (!is_power_of_2(val))
		goto unlock;
	if (br->mdb && val < br->mdb->size)
		goto unlock;

	err = 0;

	old = br->hash_max;
	br->hash_max = val;

	if (br->mdb) {
		if (br->mdb->old) {
			err = -EEXIST;
rollback:
			br->hash_max = old;
			goto unlock;
		}

		err = br_mdb_rehash(&br->mdb, br->hash_max,
				    br->hash_elasticity);
		if (err)
			goto rollback;
	}

unlock:
	spin_unlock(&br->multicast_lock);

	return err;
}