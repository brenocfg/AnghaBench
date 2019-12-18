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
struct iommu_table {scalar_t__ it_type; scalar_t__ it_index; } ;
struct dma_attrs {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int HvCallXm_setTce (int,int,int) ; 
 int TCE_ALLIO ; 
 scalar_t__ TCE_PAGE_SIZE ; 
 int TCE_PCI_READ ; 
 int TCE_PCI_WRITE ; 
 int TCE_RPN_MASK ; 
 int TCE_RPN_SHIFT ; 
 int TCE_SHIFT ; 
 int TCE_VALID ; 
 scalar_t__ TCE_VB ; 
 int TCE_VB_WRITE ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int virt_to_abs (unsigned long) ; 

__attribute__((used)) static int tce_build_iSeries(struct iommu_table *tbl, long index, long npages,
		unsigned long uaddr, enum dma_data_direction direction,
		struct dma_attrs *attrs)
{
	u64 rc;
	u64 tce, rpn;

	while (npages--) {
		rpn = virt_to_abs(uaddr) >> TCE_SHIFT;
		tce = (rpn & TCE_RPN_MASK) << TCE_RPN_SHIFT;

		if (tbl->it_type == TCE_VB) {
			/* Virtual Bus */
			tce |= TCE_VALID|TCE_ALLIO;
			if (direction != DMA_TO_DEVICE)
				tce |= TCE_VB_WRITE;
		} else {
			/* PCI Bus */
			tce |= TCE_PCI_READ; /* Read allowed */
			if (direction != DMA_TO_DEVICE)
				tce |= TCE_PCI_WRITE;
		}

		rc = HvCallXm_setTce((u64)tbl->it_index, (u64)index, tce);
		if (rc)
			panic("PCI_DMA: HvCallXm_setTce failed, Rc: 0x%llx\n",
					rc);
		index++;
		uaddr += TCE_PAGE_SIZE;
	}
	return 0;
}