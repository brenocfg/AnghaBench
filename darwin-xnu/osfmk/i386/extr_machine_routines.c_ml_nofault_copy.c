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
typedef  scalar_t__ addr64_t ;

/* Variables and functions */
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  bcopy_phys (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  i386_btop (scalar_t__) ; 
 scalar_t__ kvtophys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_valid_page (int /*<<< orphan*/ ) ; 

vm_size_t ml_nofault_copy(
	vm_offset_t virtsrc, vm_offset_t virtdst, vm_size_t size)
{
	addr64_t cur_phys_dst, cur_phys_src;
	uint32_t count, nbytes = 0;

	while (size > 0) {
		if (!(cur_phys_src = kvtophys(virtsrc)))
			break;
		if (!(cur_phys_dst = kvtophys(virtdst)))
			break;
		if (!pmap_valid_page(i386_btop(cur_phys_dst)) || !pmap_valid_page(i386_btop(cur_phys_src)))
			break;
		count = (uint32_t)(PAGE_SIZE - (cur_phys_src & PAGE_MASK));
		if (count > (PAGE_SIZE - (cur_phys_dst & PAGE_MASK)))
			count = (uint32_t)(PAGE_SIZE - (cur_phys_dst & PAGE_MASK));
		if (count > size)
			count = (uint32_t)size;

		bcopy_phys(cur_phys_src, cur_phys_dst, count);

		nbytes += count;
		virtsrc += count;
		virtdst += count;
		size -= count;
	}

	return nbytes;
}