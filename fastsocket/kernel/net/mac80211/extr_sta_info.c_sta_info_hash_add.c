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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_1__ sta; int /*<<< orphan*/  hnext; } ;
struct ieee80211_local {int /*<<< orphan*/ * sta_hash; int /*<<< orphan*/  sta_mtx; } ;

/* Variables and functions */
 size_t STA_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sta_info*) ; 

__attribute__((used)) static void sta_info_hash_add(struct ieee80211_local *local,
			      struct sta_info *sta)
{
	lockdep_assert_held(&local->sta_mtx);
	sta->hnext = local->sta_hash[STA_HASH(sta->sta.addr)];
	rcu_assign_pointer(local->sta_hash[STA_HASH(sta->sta.addr)], sta);
}