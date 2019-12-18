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
typedef  scalar_t__ uint32_t ;
struct zone_page_metadata {scalar_t__ real_metadata_offset; } ;

/* Variables and functions */
 scalar_t__ MULTIPAGE_METADATA_MAGIC ; 
 scalar_t__ PAGE_METADATA_GET_ZINDEX (struct zone_page_metadata*) ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void 
page_metadata_set_realmeta(struct zone_page_metadata *page_meta, struct zone_page_metadata *real_meta)
{
		assert(PAGE_METADATA_GET_ZINDEX(page_meta) == MULTIPAGE_METADATA_MAGIC);
		assert(PAGE_METADATA_GET_ZINDEX(real_meta) != MULTIPAGE_METADATA_MAGIC);
		assert((vm_offset_t)page_meta > (vm_offset_t)real_meta);
		vm_offset_t offset = (vm_offset_t)page_meta - (vm_offset_t)real_meta;
		assert(offset <= UINT32_MAX);
		page_meta->real_metadata_offset = (uint32_t)offset;
}