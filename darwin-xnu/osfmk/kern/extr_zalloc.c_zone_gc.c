#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* zone_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  options; } ;
struct TYPE_9__ {int /*<<< orphan*/  all_free; } ;
struct TYPE_10__ {TYPE_1__ pages; int /*<<< orphan*/  collectable; } ;

/* Variables and functions */
 int /*<<< orphan*/  TH_OPT_ZONE_GC ; 
 int ZALLOC_DEBUG_ZONEGC ; 
 TYPE_2__* ZONE_NULL ; 
 int /*<<< orphan*/  all_zones_lock ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* current_thread () ; 
 int /*<<< orphan*/  drop_free_elements (TYPE_2__*) ; 
 int /*<<< orphan*/  kill_process_in_largest_zone () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 unsigned int num_zones ; 
 scalar_t__ queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int zalloc_debug ; 
 int /*<<< orphan*/  zcache_drain_depot (TYPE_2__*) ; 
 TYPE_2__* zone_array ; 
 scalar_t__ zone_caching_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  zone_gc_lock ; 

void
zone_gc(boolean_t consider_jetsams)
{
	unsigned int	max_zones;
	zone_t			z;
	unsigned int	i;

	if (consider_jetsams) {
		kill_process_in_largest_zone();
		/*
		 * If we do end up jetsamming something, we need to do a zone_gc so that
		 * we can reclaim free zone elements and update the zone map size.
		 * Fall through.
		 */
	}

	lck_mtx_lock(&zone_gc_lock);

	current_thread()->options |= TH_OPT_ZONE_GC;

	simple_lock(&all_zones_lock);
	max_zones = num_zones;
	simple_unlock(&all_zones_lock);

	if (zalloc_debug & ZALLOC_DEBUG_ZONEGC)
		kprintf("zone_gc() starting...\n");

	for (i = 0; i < max_zones; i++) {
		z = &(zone_array[i]);
		assert(z != ZONE_NULL);

		if (!z->collectable) {
			continue;
		}
#if CONFIG_ZCACHE
		if (zone_caching_enabled(z)) {
			zcache_drain_depot(z);
		}
#endif /* CONFIG_ZCACHE */
		if (queue_empty(&z->pages.all_free)) {
			continue;
		}
		
		drop_free_elements(z);
	}

	current_thread()->options &= ~TH_OPT_ZONE_GC;

	lck_mtx_unlock(&zone_gc_lock);
}