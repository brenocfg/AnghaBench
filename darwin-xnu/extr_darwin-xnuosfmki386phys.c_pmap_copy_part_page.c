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
typedef  uintptr_t vm_size_t ;
typedef  uintptr_t vm_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  scalar_t__ pmap_paddr_t ;
typedef  scalar_t__ addr64_t ;

/* Variables and functions */
 uintptr_t INTEL_OFFMASK ; 
 uintptr_t PAGE_MASK ; 
 uintptr_t PAGE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy_phys (scalar_t__,scalar_t__,uintptr_t) ; 
 scalar_t__ i386_ptob (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 

void
pmap_copy_part_page(
	ppnum_t 	psrc,
	vm_offset_t	src_offset,
	ppnum_t	        pdst,
	vm_offset_t	dst_offset,
	vm_size_t	len)
{
        pmap_paddr_t src, dst;

	assert(psrc != vm_page_fictitious_addr);
	assert(pdst != vm_page_fictitious_addr);
	assert(psrc != vm_page_guard_addr);
	assert(pdst != vm_page_guard_addr);

	src = i386_ptob(psrc);
	dst = i386_ptob(pdst);

	assert((((uintptr_t)dst & PAGE_MASK) + dst_offset + len) <= PAGE_SIZE);
	assert((((uintptr_t)src & PAGE_MASK) + src_offset + len) <= PAGE_SIZE);

	bcopy_phys((addr64_t)src + (src_offset & INTEL_OFFMASK),
		   (addr64_t)dst + (dst_offset & INTEL_OFFMASK),
		   len);
}