#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
struct zone_cache {int zcc_depot_index; int /*<<< orphan*/  zcc_depot_lock; int /*<<< orphan*/ * zcc_depot_list; } ;
struct TYPE_4__ {struct zone_cache* zcache; } ;

/* Variables and functions */
 int ZCACHE_DEPOT_INVALID ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcache_depot_available (struct zone_cache*) ; 
 int /*<<< orphan*/  zcache_mag_drain (TYPE_1__*,int /*<<< orphan*/ ) ; 

void zcache_drain_depot(zone_t zone)
{
	struct zone_cache *zcache = zone->zcache;
	int drain_depot_index = 0;

	/*
	 * Grab the current depot list from the zone cache. If it has full magazines, 
	 * mark the depot as invalid and drain it.
	 */
	lck_mtx_lock_spin_always(&(zcache->zcc_depot_lock));
	if (!zcache_depot_available(zcache) || (zcache->zcc_depot_index == 0)) {
		/* no full magazines in the depot or depot unavailable; nothing to drain here */
		lck_mtx_unlock(&(zcache->zcc_depot_lock));
		return;
	}
	drain_depot_index = zcache->zcc_depot_index;
	/* Mark the depot as unavailable */
	zcache->zcc_depot_index = ZCACHE_DEPOT_INVALID;
	lck_mtx_unlock(&(zcache->zcc_depot_lock));

	/* Now drain the full magazines in the depot */
	for (int i = 0; i < drain_depot_index; i++)
		zcache_mag_drain(zone, zcache->zcc_depot_list[i]);

	lck_mtx_lock_spin_always(&(zcache->zcc_depot_lock));
	/* Mark the depot as available again */
	zcache->zcc_depot_index = 0;
	lck_mtx_unlock(&(zcache->zcc_depot_lock));
}