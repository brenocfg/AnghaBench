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
struct sta_info {int /*<<< orphan*/  hnext; TYPE_1__ sta; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; int /*<<< orphan*/ * sta_hash; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t STA_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct sta_info* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sta_info* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sta_info_hash_del(struct ieee80211_local *local,
			     struct sta_info *sta)
{
	struct sta_info *s;

	s = rcu_dereference_protected(local->sta_hash[STA_HASH(sta->sta.addr)],
				      lockdep_is_held(&local->sta_mtx));
	if (!s)
		return -ENOENT;
	if (s == sta) {
		rcu_assign_pointer(local->sta_hash[STA_HASH(sta->sta.addr)],
				   s->hnext);
		return 0;
	}

	while (rcu_access_pointer(s->hnext) &&
	       rcu_access_pointer(s->hnext) != sta)
		s = rcu_dereference_protected(s->hnext,
					lockdep_is_held(&local->sta_mtx));
	if (rcu_access_pointer(s->hnext)) {
		rcu_assign_pointer(s->hnext, sta->hnext);
		return 0;
	}

	return -ENOENT;
}