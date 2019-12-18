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
typedef  scalar_t__ vm_offset_t ;
struct zone_page_metadata {scalar_t__ freelist_offset; } ;

/* Variables and functions */
 scalar_t__ MULTIPAGE_METADATA_MAGIC ; 
 scalar_t__ PAGE_FOR_PAGE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_INDEX_FOR_METADATA (struct zone_page_metadata*) ; 
 scalar_t__ PAGE_METADATA_EMPTY_FREELIST ; 
 scalar_t__ PAGE_METADATA_GET_ZINDEX (struct zone_page_metadata*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ from_zone_map (struct zone_page_metadata*,int) ; 

__attribute__((used)) static inline void *
page_metadata_get_freelist(struct zone_page_metadata *page_meta)
{
	assert(PAGE_METADATA_GET_ZINDEX(page_meta) != MULTIPAGE_METADATA_MAGIC);
	if (page_meta->freelist_offset == PAGE_METADATA_EMPTY_FREELIST)
		return NULL;
	else {
		if (from_zone_map(page_meta, sizeof(struct zone_page_metadata)))
			return (void *)(PAGE_FOR_PAGE_INDEX(PAGE_INDEX_FOR_METADATA(page_meta)) + page_meta->freelist_offset);
		else
			return (void *)((vm_offset_t)page_meta + page_meta->freelist_offset);
	}
}