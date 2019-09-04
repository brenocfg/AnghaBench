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
typedef  int uint16_t ;
struct zone_page_metadata {int page_count; } ;
struct zone {int elem_size; } ;

/* Variables and functions */
 scalar_t__ MULTIPAGE_METADATA_MAGIC ; 
 scalar_t__ PAGE_METADATA_GET_ZINDEX (struct zone_page_metadata*) ; 
 struct zone* PAGE_METADATA_GET_ZONE (struct zone_page_metadata*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline uint16_t
get_metadata_alloc_count(struct zone_page_metadata *page_meta)
{
		assert(PAGE_METADATA_GET_ZINDEX(page_meta) != MULTIPAGE_METADATA_MAGIC);
		struct zone *z = PAGE_METADATA_GET_ZONE(page_meta);
		return ((page_meta->page_count * PAGE_SIZE) / z->elem_size);
}