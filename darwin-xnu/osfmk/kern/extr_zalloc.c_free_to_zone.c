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
typedef  int vm_offset_t ;
struct zone_page_metadata {int free_count; int /*<<< orphan*/  pages; scalar_t__ page_count; } ;
struct zone_free_element {int dummy; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  intermediate; int /*<<< orphan*/  all_free; int /*<<< orphan*/  any_free_foreign; } ;
struct TYPE_7__ {int /*<<< orphan*/  elem_size; int /*<<< orphan*/  countfree; int /*<<< orphan*/  count; TYPE_1__ pages; int /*<<< orphan*/  count_all_free_pages; scalar_t__ allows_foreign; int /*<<< orphan*/  zone_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASAN_HEAP_FREED ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* PAGE_METADATA_GET_ZONE (struct zone_page_metadata*) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  from_zone_map (int,int /*<<< orphan*/ ) ; 
 int* get_backup_ptr (int /*<<< orphan*/ ,int*) ; 
 int get_metadata_alloc_count (struct zone_page_metadata*) ; 
 struct zone_page_metadata* get_zone_page_metadata (struct zone_free_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sane_zone_element (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kasan_poison_range (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_metadata_get_freelist (struct zone_page_metadata*) ; 
 int /*<<< orphan*/  page_metadata_set_freelist (struct zone_page_metadata*,struct zone_free_element*) ; 
 int /*<<< orphan*/  panic (char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zp_nopoison_cookie ; 
 int zp_poisoned_cookie ; 

__attribute__((used)) static inline void
free_to_zone(zone_t      zone,
             vm_offset_t element,
             boolean_t   poison)
{
	vm_offset_t old_head;
	struct zone_page_metadata *page_meta;

	vm_offset_t *primary  = (vm_offset_t *) element;
	vm_offset_t *backup   = get_backup_ptr(zone->elem_size, primary);

	page_meta = get_zone_page_metadata((struct zone_free_element *)element, FALSE);
	assert(PAGE_METADATA_GET_ZONE(page_meta) == zone);
	old_head = (vm_offset_t)page_metadata_get_freelist(page_meta);

	if (__improbable(!is_sane_zone_element(zone, old_head)))
		panic("zfree: invalid head pointer %p for freelist of zone %s\n",
		      (void *) old_head, zone->zone_name);

	if (__improbable(!is_sane_zone_element(zone, element)))
		panic("zfree: freeing invalid pointer %p to zone %s\n",
		      (void *) element, zone->zone_name);

	if (__improbable(old_head == element))
		panic("zfree: double free of %p to zone %s\n",
		      (void *) element, zone->zone_name);
	/*
	 * Always write a redundant next pointer
	 * So that it is more difficult to forge, xor it with a random cookie
	 * A poisoned element is indicated by using zp_poisoned_cookie
	 * instead of zp_nopoison_cookie
	 */

	*backup = old_head ^ (poison ? zp_poisoned_cookie : zp_nopoison_cookie);

	/* 
	 * Insert this element at the head of the free list. We also xor the 
	 * primary pointer with the zp_nopoison_cookie to make sure a free 
	 * element does not provide the location of the next free element directly.
	 */
	*primary             = old_head ^ zp_nopoison_cookie;
	page_metadata_set_freelist(page_meta, (struct zone_free_element *)element);
	page_meta->free_count++;
	if (zone->allows_foreign && !from_zone_map(element, zone->elem_size)) {
		if (page_meta->free_count == 1) {
			/* first foreign element freed on page, move from all_used */
			re_queue_tail(&zone->pages.any_free_foreign, &(page_meta->pages));
		} else {
			/* no other list transitions */
		}
	} else if (page_meta->free_count == get_metadata_alloc_count(page_meta)) {
		/* whether the page was on the intermediate or all_used, queue, move it to free */
		re_queue_tail(&zone->pages.all_free, &(page_meta->pages));
		zone->count_all_free_pages += page_meta->page_count;
	} else if (page_meta->free_count == 1) {
		/* first free element on page, move from all_used */
		re_queue_tail(&zone->pages.intermediate, &(page_meta->pages));
	}
	zone->count--;
	zone->countfree++;

#if KASAN_ZALLOC
	kasan_poison_range(element, zone->elem_size, ASAN_HEAP_FREED);
#endif
}