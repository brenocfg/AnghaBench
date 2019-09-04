#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* zone_t ;
typedef  int vm_size_t ;
struct zone_cache {scalar_t__ zcc_depot_index; struct zcc_magazine** zcc_depot_list; int /*<<< orphan*/  zcc_depot_lock; TYPE_1__* zcc_per_cpu_caches; } ;
struct zcc_magazine {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cpu_cache_enabled; struct zone_cache* zcache; } ;
struct TYPE_6__ {struct zcc_magazine* previous; struct zcc_magazine* current; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int depot_element_count ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_zone (TYPE_2__*) ; 
 int /*<<< orphan*/  magazine_element_count ; 
 int /*<<< orphan*/  magazine_zone ; 
 int /*<<< orphan*/  unlock_zone (TYPE_2__*) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcache_locks_grp ; 
 int /*<<< orphan*/  zcache_mag_init (struct zcc_magazine*,int /*<<< orphan*/ ) ; 

void zcache_init(zone_t zone)
 {
 	int 	i;			/* used as index in for loops */
	vm_size_t	total_size;		/* Used for allocating the zone_cache struct with the proper size of depot list */
	struct zone_cache *temp_cache;	/* Temporary variable to initialize a zone_cache before assigning to the specified zone */

	/* Allocate chunk of memory for all structs */
	total_size = sizeof(struct zone_cache) + (depot_element_count * sizeof(void *));
	
	temp_cache = (struct zone_cache *) kalloc(total_size);


 	/* Initialize a cache for every CPU */
 	for (i = 0; i < MAX_CPUS; i++) {
 		temp_cache->zcc_per_cpu_caches[i].current = (struct zcc_magazine *)zalloc(magazine_zone);
 		temp_cache->zcc_per_cpu_caches[i].previous = (struct zcc_magazine *)zalloc(magazine_zone);

 		assert(temp_cache->zcc_per_cpu_caches[i].current != NULL && temp_cache->zcc_per_cpu_caches[i].previous != NULL);

 		zcache_mag_init(temp_cache->zcc_per_cpu_caches[i].current, magazine_element_count);
 		zcache_mag_init(temp_cache->zcc_per_cpu_caches[i].previous, magazine_element_count);
 	}

 	/* Initialize the lock on the depot layer */
 	lck_mtx_init(&(temp_cache->zcc_depot_lock), &zcache_locks_grp, LCK_ATTR_NULL);

	/* Initialize empty magazines in the depot list */
	for (i = 0; i < depot_element_count; i++) {
		temp_cache->zcc_depot_list[i] = (struct zcc_magazine *)zalloc(magazine_zone);

		assert(temp_cache->zcc_depot_list[i] != NULL);

		zcache_mag_init(temp_cache->zcc_depot_list[i], magazine_element_count);
	}

	temp_cache->zcc_depot_index = 0;

 	lock_zone(zone);
	zone->zcache = temp_cache;
 	/* Set flag to know caching is enabled */
 	zone->cpu_cache_enabled = TRUE;
 	unlock_zone(zone);
 	return;
 }