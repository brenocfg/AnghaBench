#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct zone_cache {scalar_t__ zcc_depot_index; int /*<<< orphan*/  zcc_depot_lock; struct zcc_per_cpu_cache* zcc_per_cpu_caches; } ;
struct zcc_per_cpu_cache {int /*<<< orphan*/  current; int /*<<< orphan*/  previous; } ;
struct TYPE_7__ {int cpu_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  elem_size; struct zone_cache* zcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASAN_HEAP_FREED ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 TYPE_5__* current_processor () ; 
 scalar_t__ depot_element_count ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  kasan_poison_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcache_canary_add (TYPE_1__*,void*) ; 
 scalar_t__ zcache_depot_available (struct zone_cache*) ; 
 int /*<<< orphan*/  zcache_mag_depot_swap_for_free (struct zone_cache*,struct zcc_per_cpu_cache*) ; 
 int /*<<< orphan*/  zcache_mag_drain (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ zcache_mag_has_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcache_mag_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zcache_swap_magazines (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool zcache_free_to_cpu_cache(zone_t zone, void *addr)
{
	int	curcpu;					/* Current cpu is used to index into array of zcc_per_cpu_cache structs */
	struct	zone_cache *zcache;			/* local storage of the zone's cache */
	struct zcc_per_cpu_cache *per_cpu_cache;	/* locally store the current per_cpu_cache */

	disable_preemption();
	curcpu = current_processor()->cpu_id;
	zcache = zone->zcache;
	per_cpu_cache = &zcache->zcc_per_cpu_caches[curcpu];

	if (zcache_mag_has_space(per_cpu_cache->current)) {
		/* If able, free into current magazine */
		goto free_to_current;
	} else if (zcache_mag_has_space(per_cpu_cache->previous)) {
		/* If able, swap current and previous magazine and retry */
		zcache_swap_magazines(&per_cpu_cache->previous, &per_cpu_cache->current);
		goto free_to_current;
	} else{
		lck_mtx_lock_spin_always(&(zcache->zcc_depot_lock));
		if (zcache_depot_available(zcache) && (zcache->zcc_depot_index < depot_element_count)) {
			/* If able, rotate in a new empty magazine from the depot and retry */
			zcache_mag_depot_swap_for_free(zcache, per_cpu_cache);
			lck_mtx_unlock(&(zcache->zcc_depot_lock));
			goto free_to_current;
		}
		lck_mtx_unlock(&(zcache->zcc_depot_lock));
		/* Attempt to free an entire magazine of elements */
		zcache_mag_drain(zone, per_cpu_cache->current);
		if(zcache_mag_has_space(per_cpu_cache->current)){
			goto free_to_current;
		}
	}

	/* If not able to use cache return FALSE and fall through to zfree */
	enable_preemption();
	return FALSE;

free_to_current:
	assert(zcache_mag_has_space(per_cpu_cache->current));
	zcache_canary_add(zone, addr);
	zcache_mag_push(per_cpu_cache->current, addr);

#if KASAN_ZALLOC
	kasan_poison_range((vm_offset_t)addr, zone->elem_size, ASAN_HEAP_FREED);
#endif

	enable_preemption();
	return TRUE;
}