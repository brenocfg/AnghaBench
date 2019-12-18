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
typedef  int u32 ;
struct iommu {int /*<<< orphan*/  page_table_lock; } ;

/* Variables and functions */
 int IOPGD_SHIFT ; 
 int IOPGD_TABLE ; 
 int PTRS_PER_IOPGD ; 
 int /*<<< orphan*/  flush_iopgd_range (int*,int*) ; 
 int /*<<< orphan*/  flush_iotlb_all (struct iommu*) ; 
 int* iopgd_offset (struct iommu*,int) ; 
 int /*<<< orphan*/  iopte_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iopte_offset (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iopgtable_clear_entry_all(struct iommu *obj)
{
	int i;

	spin_lock(&obj->page_table_lock);

	for (i = 0; i < PTRS_PER_IOPGD; i++) {
		u32 da;
		u32 *iopgd;

		da = i << IOPGD_SHIFT;
		iopgd = iopgd_offset(obj, da);

		if (!*iopgd)
			continue;

		if (*iopgd & IOPGD_TABLE)
			iopte_free(iopte_offset(iopgd, 0));

		*iopgd = 0;
		flush_iopgd_range(iopgd, iopgd);
	}

	flush_iotlb_all(obj);

	spin_unlock(&obj->page_table_lock);
}