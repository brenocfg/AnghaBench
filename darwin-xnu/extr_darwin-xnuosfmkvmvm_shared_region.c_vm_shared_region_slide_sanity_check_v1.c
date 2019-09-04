#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_shared_region_slide_info_entry_v1_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {size_t toc_count; int entry_count; scalar_t__ toc_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,size_t,int,int) ; 

__attribute__((used)) static kern_return_t
vm_shared_region_slide_sanity_check_v1(vm_shared_region_slide_info_entry_v1_t s_info)
{
	uint32_t pageIndex=0;
	uint16_t entryIndex=0;
	uint16_t *toc = NULL;

	toc = (uint16_t*)((uintptr_t)s_info + s_info->toc_offset);
	for (;pageIndex < s_info->toc_count; pageIndex++) {

		entryIndex =  (uint16_t)(toc[pageIndex]);

		if (entryIndex >= s_info->entry_count) {
			printf("No sliding bitmap entry for pageIndex: %d at entryIndex: %d amongst %d entries\n", pageIndex, entryIndex, s_info->entry_count);
			return KERN_FAILURE;
		}

	}
	return KERN_SUCCESS;
}