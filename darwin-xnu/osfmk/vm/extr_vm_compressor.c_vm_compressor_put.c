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
typedef  int uint64_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int pmap_paddr_t ;
typedef  int /*<<< orphan*/  c_slot_mapping_t ;
typedef  int /*<<< orphan*/  c_segment_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 char* PHYSMAP_PTOV (int) ; 
 int c_compress_page (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ phystokv (int) ; 

int
vm_compressor_put(ppnum_t pn, int *slot, void  **current_chead, char *scratch_buf)
{
	char	*src;
	int	retval;

#if __x86_64__
	src = PHYSMAP_PTOV((uint64_t)pn << (uint64_t)PAGE_SHIFT);
#elif __arm__ || __arm64__
	src = (char *) phystokv((pmap_paddr_t)pn << PAGE_SHIFT);
#else
#error "unsupported architecture"
#endif

	retval = c_compress_page(src, (c_slot_mapping_t)slot, (c_segment_t *)current_chead, scratch_buf);

	return (retval);
}