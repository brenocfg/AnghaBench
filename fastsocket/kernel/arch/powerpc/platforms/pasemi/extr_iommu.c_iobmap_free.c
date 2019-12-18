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
typedef  int /*<<< orphan*/  u32 ;
struct iommu_table {long it_offset; scalar_t__ it_base; } ;

/* Variables and functions */
 long IOBMAP_PAGE_SHIFT ; 
 scalar_t__ IOBMAP_PAGE_SIZE ; 
 scalar_t__ IOB_AT_INVAL_TLB_REG ; 
 scalar_t__ iob ; 
 int /*<<< orphan*/  iob_l2_emptyval ; 
 int /*<<< orphan*/  out_le32 (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,long,long) ; 

__attribute__((used)) static void iobmap_free(struct iommu_table *tbl, long index,
			long npages)
{
	u32 *ip;
	unsigned long bus_addr;

	pr_debug("iobmap: free at: %lx, %lx\n", index, npages);

	bus_addr = (tbl->it_offset + index) << IOBMAP_PAGE_SHIFT;

	ip = ((u32 *)tbl->it_base) + index;

	while (npages--) {
		*(ip++) = iob_l2_emptyval;
		/* invalidate tlb, can be optimized more */
		out_le32(iob+IOB_AT_INVAL_TLB_REG, bus_addr >> 14);
		bus_addr += IOBMAP_PAGE_SIZE;
	}
}