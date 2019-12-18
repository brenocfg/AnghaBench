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
struct iotlb_entry {int /*<<< orphan*/  da; } ;
struct iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_iotlb_page (struct iommu*,int /*<<< orphan*/ ) ; 
 int iopgtable_store_entry_core (struct iommu*,struct iotlb_entry*) ; 
 int /*<<< orphan*/  load_iotlb_entry (struct iommu*,struct iotlb_entry*) ; 

int iopgtable_store_entry(struct iommu *obj, struct iotlb_entry *e)
{
	int err;

	flush_iotlb_page(obj, e->da);
	err = iopgtable_store_entry_core(obj, e);
#ifdef PREFETCH_IOTLB
	if (!err)
		load_iotlb_entry(obj, e);
#endif
	return err;
}