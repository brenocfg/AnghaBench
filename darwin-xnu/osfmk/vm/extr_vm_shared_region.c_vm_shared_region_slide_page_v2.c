#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_shared_region_slide_info_t ;
typedef  TYPE_3__* vm_shared_region_slide_info_entry_v2_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int boolean_t ;
struct TYPE_8__ {int delta_mask; int page_starts_count; int page_extras_count; scalar_t__ page_extras_offset; scalar_t__ page_starts_offset; } ;
struct TYPE_7__ {int slide; TYPE_1__* slide_info_entry; } ;
struct TYPE_6__ {TYPE_3__ v2; } ;

/* Variables and functions */
 int DYLD_CACHE_SLIDE_PAGE_ATTR_END ; 
 int DYLD_CACHE_SLIDE_PAGE_ATTR_EXTRA ; 
 int DYLD_CACHE_SLIDE_PAGE_ATTR_NO_REBASE ; 
 int DYLD_CACHE_SLIDE_PAGE_OFFSET_SHIFT ; 
 int DYLD_CACHE_SLIDE_PAGE_VALUE ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ rebase_chain (int const,int,int /*<<< orphan*/ *,int const,int const,TYPE_3__*) ; 

__attribute__((used)) static kern_return_t
vm_shared_region_slide_page_v2(vm_shared_region_slide_info_t si, vm_offset_t vaddr, uint32_t pageIndex)
{
	vm_shared_region_slide_info_entry_v2_t s_info = &si->slide_info_entry->v2;
	const uint32_t slide_amount = si->slide;

	/* The high bits of the delta_mask field are nonzero precisely when the shared
	 * cache is 64-bit. */
	const boolean_t is_64 = (s_info->delta_mask >> 32) != 0;

	const uint16_t *page_starts = (uint16_t *)((uintptr_t)s_info + s_info->page_starts_offset);
	const uint16_t *page_extras = (uint16_t *)((uintptr_t)s_info + s_info->page_extras_offset);

	uint8_t *page_content = (uint8_t *)vaddr;
	uint16_t page_entry;

	if (pageIndex >= s_info->page_starts_count) {
		printf("vm_shared_region_slide_page() did not find page start in slide info: pageIndex=%u, count=%u\n",
		       pageIndex, s_info->page_starts_count);
		return KERN_FAILURE;
	}
	page_entry = page_starts[pageIndex];

	if (page_entry == DYLD_CACHE_SLIDE_PAGE_ATTR_NO_REBASE) {
		return KERN_SUCCESS;
	}

	if (page_entry & DYLD_CACHE_SLIDE_PAGE_ATTR_EXTRA) {
		uint16_t chain_index = page_entry & DYLD_CACHE_SLIDE_PAGE_VALUE;
		uint16_t info;

		do {
			uint16_t page_start_offset;
			kern_return_t kr;

			if (chain_index >= s_info->page_extras_count) {
				printf("vm_shared_region_slide_page() out-of-bounds extras index: index=%u, count=%u\n",
				       chain_index, s_info->page_extras_count);
				return KERN_FAILURE;
			}
			info = page_extras[chain_index];
			page_start_offset = (info & DYLD_CACHE_SLIDE_PAGE_VALUE) << DYLD_CACHE_SLIDE_PAGE_OFFSET_SHIFT;

			kr = rebase_chain(is_64, pageIndex, page_content, page_start_offset, slide_amount, s_info);
			if (kr != KERN_SUCCESS) {
				return KERN_FAILURE;
			}

			chain_index++;
		} while (!(info & DYLD_CACHE_SLIDE_PAGE_ATTR_END));
	} else {
		const uint32_t page_start_offset = page_entry << DYLD_CACHE_SLIDE_PAGE_OFFSET_SHIFT;
		kern_return_t kr;

		kr = rebase_chain(is_64, pageIndex, page_content, page_start_offset, slide_amount, s_info);
		if (kr != KERN_SUCCESS) {
			return KERN_FAILURE;
		}
	}

	return KERN_SUCCESS;
}