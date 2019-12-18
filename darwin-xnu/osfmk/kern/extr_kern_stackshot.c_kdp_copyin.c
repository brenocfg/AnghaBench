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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 size_t MIN (size_t,size_t) ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  bcopy_phys (size_t,size_t,size_t) ; 
 scalar_t__ gPanicBase ; 
 scalar_t__ gPanicSize ; 
 size_t kdp_find_phys (int /*<<< orphan*/ ,size_t,int,size_t*) ; 
 size_t kvtophys (scalar_t__) ; 
 scalar_t__ panic_stackshot ; 
 scalar_t__ phystokv (size_t) ; 
 int /*<<< orphan*/  stackshot_memcpy (char*,void const*,size_t) ; 

boolean_t
kdp_copyin(vm_map_t map, uint64_t uaddr, void *dest, size_t size, boolean_t try_fault, uint32_t *kdp_fault_results)
{
	size_t rem = size;
	char *kvaddr = dest;

#if CONFIG_EMBEDDED
	/* Identify if destination buffer is in panic storage area */
	if (panic_stackshot && ((vm_offset_t)dest >= gPanicBase) && ((vm_offset_t)dest < (gPanicBase + gPanicSize))) {
		if (((vm_offset_t)dest + size) > (gPanicBase + gPanicSize)) {
			return FALSE;
		}
	}
#endif

	while (rem) {
		uint64_t phys_src = kdp_find_phys(map, uaddr, try_fault, kdp_fault_results);
		uint64_t phys_dest = kvtophys((vm_offset_t)kvaddr);
		uint64_t src_rem = PAGE_SIZE - (phys_src & PAGE_MASK);
		uint64_t dst_rem = PAGE_SIZE - (phys_dest & PAGE_MASK);
		size_t cur_size = (uint32_t) MIN(src_rem, dst_rem);
		cur_size = MIN(cur_size, rem);

		if (phys_src && phys_dest) {
#if CONFIG_EMBEDDED
			/*
			 * On embedded the panic buffer is mapped as device memory and doesn't allow
			 * unaligned accesses. To prevent these, we copy over bytes individually here.
			 */
			if (panic_stackshot)
				stackshot_memcpy(kvaddr, (const void *)phystokv(phys_src), cur_size);
			else
#endif /* CONFIG_EMBEDDED */
				bcopy_phys(phys_src, phys_dest, cur_size);
		} else {
			break;
		}

		uaddr += cur_size;
		kvaddr += cur_size;
		rem -= cur_size;
	}

	return (rem == 0);
}