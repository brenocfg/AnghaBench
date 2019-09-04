#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_shared_region_slide_info_t ;
typedef  TYPE_3__* vm_shared_region_slide_info_entry_v1_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ vaddr ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  TYPE_4__* slide_info_entry_toc_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_9__ {int* entry; } ;
struct TYPE_8__ {int toc_count; int entry_count; scalar_t__ entry_offset; scalar_t__ toc_offset; } ;
struct TYPE_7__ {int slide; TYPE_1__* slide_info_entry; } ;
struct TYPE_6__ {TYPE_3__ v1; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int NUM_SLIDING_BITMAPS_PER_PAGE ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int task_has_64Bit_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vm_shared_region_slide_page_v1(vm_shared_region_slide_info_t si, vm_offset_t vaddr, uint32_t pageIndex)
{
	uint16_t *toc = NULL;
	slide_info_entry_toc_t bitmap = NULL;
	uint32_t i=0, j=0;
	uint8_t b = 0;
	uint32_t slide = si->slide;
	int is_64 = task_has_64Bit_addr(current_task());

	vm_shared_region_slide_info_entry_v1_t s_info = &si->slide_info_entry->v1;
	toc = (uint16_t*)((uintptr_t)s_info + s_info->toc_offset);
	
	if (pageIndex >= s_info->toc_count) {
		printf("No slide entry for this page in toc. PageIndex: %d Toc Count: %d\n", pageIndex, s_info->toc_count);
	} else {
		uint16_t entryIndex =  (uint16_t)(toc[pageIndex]);
		slide_info_entry_toc_t slide_info_entries = (slide_info_entry_toc_t)((uintptr_t)s_info + s_info->entry_offset);
		
		if (entryIndex >= s_info->entry_count) {
			printf("No sliding bitmap entry for entryIndex: %d amongst %d entries\n", entryIndex, s_info->entry_count);
		} else {
			bitmap = &slide_info_entries[entryIndex];

			for(i=0; i < NUM_SLIDING_BITMAPS_PER_PAGE; ++i) {
				b = bitmap->entry[i];
				if (b!=0) {
					for (j=0; j <8; ++j) {
						if (b & (1 <<j)){
							uint32_t *ptr_to_slide;
							uint32_t old_value;

							ptr_to_slide = (uint32_t*)((uintptr_t)(vaddr)+(sizeof(uint32_t)*(i*8 +j)));
							old_value = *ptr_to_slide;
							*ptr_to_slide += slide;
							if (is_64 && *ptr_to_slide < old_value) {
								/*
								 * We just slid the low 32 bits of a 64-bit pointer
								 * and it looks like there should have been a carry-over
								 * to the upper 32 bits.
								 * The sliding failed...
								 */
								printf("vm_shared_region_slide() carry over: i=%d j=%d b=0x%x slide=0x%x old=0x%x new=0x%x\n",
								       i, j, b, slide, old_value, *ptr_to_slide);
								return KERN_FAILURE;
							}
						}
					}
				}
			}
		}
	}

	return KERN_SUCCESS;
}