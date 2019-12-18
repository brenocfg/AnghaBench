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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct zone_page_metadata {int dummy; } ;
struct zone_free_element {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ MULTIPAGE_METADATA_MAGIC ; 
 scalar_t__ PAGE_METADATA_FOR_ELEMENT (struct zone_free_element*) ; 
 scalar_t__ PAGE_METADATA_GET_ZINDEX (struct zone_page_metadata*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ from_zone_map (struct zone_free_element*,int) ; 
 struct zone_page_metadata* page_metadata_get_realmeta (struct zone_page_metadata*) ; 
 scalar_t__ trunc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_populate_metadata_page (struct zone_page_metadata*) ; 

__attribute__((used)) static inline struct zone_page_metadata *
get_zone_page_metadata(struct zone_free_element *element, boolean_t init)
{
	struct zone_page_metadata *page_meta = 0;

	if (from_zone_map(element, sizeof(struct zone_free_element))) {	
		page_meta = (struct zone_page_metadata *)(PAGE_METADATA_FOR_ELEMENT(element));
		if (init)
			zone_populate_metadata_page(page_meta);
	} else {
		page_meta = (struct zone_page_metadata *)(trunc_page((vm_offset_t)element));
	}
	if (init) {
		bzero((char *)page_meta, sizeof(struct zone_page_metadata));
	}
	return ((PAGE_METADATA_GET_ZINDEX(page_meta) != MULTIPAGE_METADATA_MAGIC) ? page_meta : page_metadata_get_realmeta(page_meta));
}