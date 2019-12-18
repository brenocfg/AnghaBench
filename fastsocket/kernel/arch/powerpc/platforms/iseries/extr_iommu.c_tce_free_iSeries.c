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
typedef  scalar_t__ u64 ;
struct iommu_table {scalar_t__ it_index; } ;

/* Variables and functions */
 scalar_t__ HvCallXm_setTce (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

__attribute__((used)) static void tce_free_iSeries(struct iommu_table *tbl, long index, long npages)
{
	u64 rc;

	while (npages--) {
		rc = HvCallXm_setTce((u64)tbl->it_index, (u64)index, 0);
		if (rc)
			panic("PCI_DMA: HvCallXm_setTce failed, Rc: 0x%llx\n",
					rc);
		index++;
	}
}