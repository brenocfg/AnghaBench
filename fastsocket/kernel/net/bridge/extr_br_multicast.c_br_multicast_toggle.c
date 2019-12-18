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
struct net_bridge {int multicast_disabled; int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  hash_elasticity; TYPE_1__* mdb; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  max; scalar_t__ old; } ;

/* Variables and functions */
 int EEXIST ; 
 int br_mdb_rehash (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_multicast_start_querier (struct net_bridge*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int br_multicast_toggle(struct net_bridge *br, unsigned long val)
{
	int err = 0;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev))
		goto unlock;

	if (br->multicast_disabled == !val)
		goto unlock;

	br->multicast_disabled = !val;
	if (br->multicast_disabled)
		goto unlock;

	if (br->mdb) {
		if (br->mdb->old) {
			err = -EEXIST;
rollback:
			br->multicast_disabled = !!val;
			goto unlock;
		}

		err = br_mdb_rehash(&br->mdb, br->mdb->max,
				    br->hash_elasticity);
		if (err)
			goto rollback;
	}

	br_multicast_start_querier(br);

unlock:
	spin_unlock(&br->multicast_lock);

	return err;
}