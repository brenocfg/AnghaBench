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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int kvtophys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_valid_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page_64 (int) ; 

boolean_t ml_validate_nofault(
	vm_offset_t virtsrc, vm_size_t size)
{
	addr64_t cur_phys_src;
	uint32_t count;

	while (size > 0) {
		if (!(cur_phys_src = kvtophys(virtsrc)))
			return FALSE;
		if (!pmap_valid_address(trunc_page_64(cur_phys_src)))
			return FALSE;
		count = (uint32_t)(PAGE_SIZE - (cur_phys_src & PAGE_MASK));
		if (count > size)
			count = (uint32_t)size;

		virtsrc += count;
		size -= count;
	}

	return TRUE;
}