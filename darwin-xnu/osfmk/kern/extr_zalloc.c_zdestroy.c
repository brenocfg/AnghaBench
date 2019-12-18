#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* zone_t ;
struct TYPE_9__ {int /*<<< orphan*/  all_free; int /*<<< orphan*/  intermediate; int /*<<< orphan*/  all_used; } ;
struct TYPE_10__ {int zone_valid; int doing_alloc_without_vm_priv; int doing_alloc_with_vm_priv; int async_pending; int waiting; int async_prio_refill; scalar_t__ count; scalar_t__ countfree; scalar_t__ cur_size; scalar_t__ page_count; scalar_t__ count_all_free_pages; unsigned int index; TYPE_1__ pages; int /*<<< orphan*/  zone_name; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  all_zones_lock ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_test (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  drop_free_elements (TYPE_2__*) ; 
 int /*<<< orphan*/  gzalloc_empty_free_cache (TYPE_2__*) ; 
 int /*<<< orphan*/  lock_zone (TYPE_2__*) ; 
 scalar_t__ num_zones_in_use ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_zone (TYPE_2__*) ; 
 scalar_t__ zone_caching_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  zone_empty_bitmap ; 

void
zdestroy(zone_t z)
{
	unsigned int zindex;

	assert(z != NULL);

	lock_zone(z);
	assert(z->zone_valid);

	/* Assert that the zone does not have any allocations in flight */
	assert(z->doing_alloc_without_vm_priv == FALSE);
	assert(z->doing_alloc_with_vm_priv == FALSE);
	assert(z->async_pending == FALSE);
	assert(z->waiting == FALSE);
	assert(z->async_prio_refill == FALSE);

#if !KASAN_ZALLOC
	/*
	 * Unset the valid bit. We'll hit an assert failure on further operations on this zone, until zinit() is called again.
	 * Leave the zone valid for KASan as we will see zfree's on quarantined free elements even after the zone is destroyed.
	 */
	z->zone_valid = FALSE;
#endif
	unlock_zone(z);

#if CONFIG_ZCACHE
	/* Drain the per-cpu caches if caching is enabled for the zone. */
	if (zone_caching_enabled(z)) {
		panic("zdestroy: Zone caching enabled for zone %s", z->zone_name);
	}
#endif /* CONFIG_ZCACHE */

	/* Dump all the free elements */
	drop_free_elements(z);

#if	CONFIG_GZALLOC
	/* If the zone is gzalloc managed dump all the elements in the free cache */
	gzalloc_empty_free_cache(z);
#endif

	lock_zone(z);

#if !KASAN_ZALLOC
	/* Assert that all counts are zero */
	assert(z->count == 0);
	assert(z->countfree == 0);
	assert(z->cur_size == 0);
	assert(z->page_count == 0);
	assert(z->count_all_free_pages == 0);

	/* Assert that all queues except the foreign queue are empty. The zone allocator doesn't know how to free up foreign memory. */
	assert(queue_empty(&z->pages.all_used));
	assert(queue_empty(&z->pages.intermediate));
	assert(queue_empty(&z->pages.all_free));
#endif

	zindex = z->index;

	unlock_zone(z);

	simple_lock(&all_zones_lock);

	assert(!bitmap_test(zone_empty_bitmap, zindex));
	/* Mark the zone as empty in the bitmap */
	bitmap_set(zone_empty_bitmap, zindex);
	num_zones_in_use--;
	assert(num_zones_in_use > 0);

	simple_unlock(&all_zones_lock);
}