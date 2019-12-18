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
struct ieee80211_sub_if_data {int /*<<< orphan*/  default_multicast_key; int /*<<< orphan*/  local; int /*<<< orphan*/  default_unicast_key; int /*<<< orphan*/ * keys; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 int NUM_DEFAULT_KEYS ; 
 int /*<<< orphan*/  assert_key_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_set_default_unicast_key (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_debugfs_key_update_default (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_key* key_mtx_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_key*) ; 

__attribute__((used)) static void __ieee80211_set_default_key(struct ieee80211_sub_if_data *sdata,
					int idx, bool uni, bool multi)
{
	struct ieee80211_key *key = NULL;

	assert_key_lock(sdata->local);

	if (idx >= 0 && idx < NUM_DEFAULT_KEYS)
		key = key_mtx_dereference(sdata->local, sdata->keys[idx]);

	if (uni) {
		rcu_assign_pointer(sdata->default_unicast_key, key);
		drv_set_default_unicast_key(sdata->local, sdata, idx);
	}

	if (multi)
		rcu_assign_pointer(sdata->default_multicast_key, key);

	ieee80211_debugfs_key_update_default(sdata);
}