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
 int /*<<< orphan*/  ASAN_VALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* current_processor () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  kasan_poison_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcache_canary_validate (TYPE_1__*,void*) ; 
 scalar_t__ zcache_depot_available (struct zone_cache*) ; 
 int /*<<< orphan*/  zcache_mag_depot_swap_for_alloc (struct zone_cache*,struct zcc_per_cpu_cache*) ; 
 scalar_t__ zcache_mag_fill (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ zcache_mag_has_elements (int /*<<< orphan*/ ) ; 
 void* zcache_mag_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcache_swap_magazines (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

vm_offset_t zcache_alloc_from_cpu_cache(zone_t zone)
{
	int curcpu;					/* Current cpu is used to index into array of zcc_per_cpu_cache structs */
	void *ret = NULL;				/* Points to the element which will be returned */
	struct	zone_cache *zcache;			/* local storage of the zone's cache */
	struct zcc_per_cpu_cache *per_cpu_cache; 	/* locally store the current per_cpu_cache */

	disable_preemption();
	curcpu = current_processor()->cpu_id;
	zcache = zone->zcache;
	per_cpu_cache = &zcache->zcc_per_cpu_caches[curcpu];

	if (zcache_mag_has_elements(per_cpu_cache->current)) {
		/* If able, allocate from current magazine */
		goto allocate_from_current;
	} else if (zcache_mag_has_elements(per_cpu_cache->previous)) {
		/* If able, swap current and previous magazine and retry */
		zcache_swap_magazines(&per_cpu_cache->previous, &per_cpu_cache->current);
		goto allocate_from_current;
	} else {
		lck_mtx_lock_spin_always(&(zcache->zcc_depot_lock));
		if (zcache_depot_available(zcache) && (zcache->zcc_depot_index > 0)) {
			/* If able, rotate in a full magazine from the depot */
			zcache_mag_depot_swap_for_alloc(zcache, per_cpu_cache);
			lck_mtx_unlock(&(zcache->zcc_depot_lock));
			goto allocate_from_current;
		}
		lck_mtx_unlock(&(zcache->zcc_depot_lock));
		/* Attempt to allocate an entire magazine of elements */
		if(zcache_mag_fill(zone, per_cpu_cache->current)){
			goto allocate_from_current;
		}
	}

	/* If unable to allocate from cache return NULL and fall through to zalloc */
	enable_preemption();
	return (vm_offset_t) NULL;

allocate_from_current:
	ret = zcache_mag_pop(per_cpu_cache->current);
	assert(ret != NULL);
	zcache_canary_validate(zone, ret);

#if KASAN_ZALLOC
	kasan_poison_range((vm_offset_t)ret, zone->elem_size, ASAN_VALID);
#endif

	enable_preemption();
	return (vm_offset_t) ret;
}