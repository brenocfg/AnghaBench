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
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int amd_iommu_last_bdf ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_queue_inv_dev_entry (struct amd_iommu*,int) ; 

__attribute__((used)) static void flush_all_devices_for_iommu(struct amd_iommu *iommu)
{
	int i;

	for (i = 0; i <= amd_iommu_last_bdf; ++i) {
		if (iommu != amd_iommu_rlookup_table[i])
			continue;

		iommu_queue_inv_dev_entry(iommu, i);
		iommu_completion_wait(iommu);
	}
}