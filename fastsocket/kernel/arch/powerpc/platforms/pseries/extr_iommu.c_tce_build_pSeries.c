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
typedef  int u64 ;
struct iommu_table {scalar_t__ it_base; } ;
struct dma_attrs {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 scalar_t__ TCE_PAGE_SIZE ; 
 int TCE_PCI_READ ; 
 int TCE_PCI_WRITE ; 
 int TCE_RPN_MASK ; 
 int TCE_RPN_SHIFT ; 
 int TCE_SHIFT ; 
 int virt_to_abs (unsigned long) ; 

__attribute__((used)) static int tce_build_pSeries(struct iommu_table *tbl, long index,
			      long npages, unsigned long uaddr,
			      enum dma_data_direction direction,
			      struct dma_attrs *attrs)
{
	u64 proto_tce;
	u64 *tcep;
	u64 rpn;

	proto_tce = TCE_PCI_READ; // Read allowed

	if (direction != DMA_TO_DEVICE)
		proto_tce |= TCE_PCI_WRITE;

	tcep = ((u64 *)tbl->it_base) + index;

	while (npages--) {
		/* can't move this out since we might cross LMB boundary */
		rpn = (virt_to_abs(uaddr)) >> TCE_SHIFT;
		*tcep = proto_tce | (rpn & TCE_RPN_MASK) << TCE_RPN_SHIFT;

		uaddr += TCE_PAGE_SIZE;
		tcep++;
	}
	return 0;
}