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
typedef  int vm_map_size_t ;
typedef  int vm_map_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TEST_PAGE_SIZE_4K ; 
 int /*<<< orphan*/  TRUE ; 
 int VREGION1_SIZE ; 
 int VREGION1_START ; 
 int gVirtBase ; 
 int virtual_space_start ; 

boolean_t
pmap_virtual_region(
	unsigned int region_select,
	vm_map_offset_t *startp,
	vm_map_size_t *size
)
{
	boolean_t	ret = FALSE;
#if	__ARM64_PMAP_SUBPAGE_L1__ && __ARM_16K_PG__
	if (region_select == 0) {
		/*
		 * In this config, the bootstrap mappings should occupy their own L2
		 * TTs, as they should be immutable after boot.  Having the associated
		 * TTEs and PTEs in their own pages allows us to lock down those pages,
		 * while allowing the rest of the kernel address range to be remapped.
		 */
#if	(__ARM_VMSA__ > 7)
		*startp = LOW_GLOBAL_BASE_ADDRESS & ~ARM_TT_L2_OFFMASK;
#else
#error Unsupported configuration
#endif
		*size = ((VM_MAX_KERNEL_ADDRESS - *startp) & ~PAGE_MASK);
		ret = TRUE;
	}
#else
#if     (__ARM_VMSA__ > 7)
	unsigned long low_global_vr_mask = 0;
	vm_map_size_t low_global_vr_size = 0;
#endif

	if (region_select == 0) {
#if	(__ARM_VMSA__ == 7)
		*startp = gVirtBase & 0xFFC00000;
		*size = ((virtual_space_start-(gVirtBase & 0xFFC00000)) + ~0xFFC00000) & 0xFFC00000;
#else
		/* Round to avoid overlapping with the V=P area; round to at least the L2 block size. */
		if (!TEST_PAGE_SIZE_4K) {
			*startp = gVirtBase & 0xFFFFFFFFFE000000;
			*size = ((virtual_space_start-(gVirtBase & 0xFFFFFFFFFE000000)) + ~0xFFFFFFFFFE000000) & 0xFFFFFFFFFE000000;
		} else {
			*startp = gVirtBase & 0xFFFFFFFFFF800000;
			*size = ((virtual_space_start-(gVirtBase & 0xFFFFFFFFFF800000)) + ~0xFFFFFFFFFF800000) & 0xFFFFFFFFFF800000;
		}
#endif
		ret = TRUE;
	}
	if (region_select == 1) {
		*startp = VREGION1_START;
		*size = VREGION1_SIZE;
		ret = TRUE;
	}
#if	(__ARM_VMSA__ > 7)
	/* We need to reserve a range that is at least the size of an L2 block mapping for the low globals */
	if (!TEST_PAGE_SIZE_4K) {
		low_global_vr_mask = 0xFFFFFFFFFE000000;
		low_global_vr_size = 0x2000000;
	} else {
		low_global_vr_mask = 0xFFFFFFFFFF800000;
		low_global_vr_size = 0x800000;
	}

	if (((gVirtBase & low_global_vr_mask) != LOW_GLOBAL_BASE_ADDRESS)  && (region_select == 2)) {
		*startp = LOW_GLOBAL_BASE_ADDRESS;
		*size = low_global_vr_size;
		ret = TRUE;
	}

	if (region_select == 3) {
		/* In this config, we allow the bootstrap mappings to occupy the same
		 * page table pages as the heap.
		 */
		*startp = VM_MIN_KERNEL_ADDRESS;
		*size = LOW_GLOBAL_BASE_ADDRESS - *startp;
		ret = TRUE;
	}
#endif
#endif
	return ret;
}