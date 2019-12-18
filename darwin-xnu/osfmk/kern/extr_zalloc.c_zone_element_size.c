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
typedef  struct zone* zone_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
struct zone_page_metadata {int dummy; } ;
struct zone_free_element {int dummy; } ;
struct zone {int /*<<< orphan*/  elem_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct zone* PAGE_METADATA_GET_ZONE (struct zone_page_metadata*) ; 
 scalar_t__ from_zone_map (void*,int) ; 
 struct zone_page_metadata* get_zone_page_metadata (struct zone_free_element*,int /*<<< orphan*/ ) ; 
 scalar_t__ gzalloc_element_size (void*,struct zone**,int /*<<< orphan*/ *) ; 

vm_size_t
zone_element_size(void *addr, zone_t *z)
{
	struct zone *src_zone;
	if (from_zone_map(addr, sizeof(void *))) {
		struct zone_page_metadata *page_meta = get_zone_page_metadata((struct zone_free_element *)addr, FALSE);
		src_zone = PAGE_METADATA_GET_ZONE(page_meta);
		if (z) {
			*z = src_zone;
		}
		return (src_zone->elem_size);
	} else {
#if CONFIG_GZALLOC
		vm_size_t gzsize;
		if (gzalloc_element_size(addr, z, &gzsize)) {
			return gzsize;
		}
#endif /* CONFIG_GZALLOC */

		return 0;
	}
}