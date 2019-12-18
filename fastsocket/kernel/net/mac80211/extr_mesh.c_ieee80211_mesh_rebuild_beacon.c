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
struct ieee80211_if_mesh {int /*<<< orphan*/  mtx; int /*<<< orphan*/  beacon; } ;
struct beacon_data {int dummy; } ;

/* Variables and functions */
 int ieee80211_mesh_build_beacon (struct ieee80211_if_mesh*) ; 
 int /*<<< orphan*/  kfree_rcu (struct beacon_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct beacon_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static int
ieee80211_mesh_rebuild_beacon(struct ieee80211_if_mesh *ifmsh)
{
	struct beacon_data *old_bcn;
	int ret;

	mutex_lock(&ifmsh->mtx);

	old_bcn = rcu_dereference_protected(ifmsh->beacon,
					    lockdep_is_held(&ifmsh->mtx));
	ret = ieee80211_mesh_build_beacon(ifmsh);
	if (ret)
		/* just reuse old beacon */
		goto out;

	if (old_bcn)
		kfree_rcu(old_bcn, rcu_head);
out:
	mutex_unlock(&ifmsh->mtx);
	return ret;
}