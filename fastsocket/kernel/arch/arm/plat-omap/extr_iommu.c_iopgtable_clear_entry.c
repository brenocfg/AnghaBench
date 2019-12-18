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
struct iommu {int /*<<< orphan*/  page_table_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_iotlb_page (struct iommu*,int /*<<< orphan*/ ) ; 
 size_t iopgtable_clear_entry_core (struct iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

size_t iopgtable_clear_entry(struct iommu *obj, u32 da)
{
	size_t bytes;

	spin_lock(&obj->page_table_lock);

	bytes = iopgtable_clear_entry_core(obj, da);
	flush_iotlb_page(obj, da);

	spin_unlock(&obj->page_table_lock);

	return bytes;
}