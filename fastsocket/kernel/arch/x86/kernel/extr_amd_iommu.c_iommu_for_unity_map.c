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
typedef  size_t u16 ;
struct unity_map_entry {size_t devid_start; size_t devid_end; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 size_t* amd_iommu_alias_table ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 

__attribute__((used)) static int iommu_for_unity_map(struct amd_iommu *iommu,
			       struct unity_map_entry *entry)
{
	u16 bdf, i;

	for (i = entry->devid_start; i <= entry->devid_end; ++i) {
		bdf = amd_iommu_alias_table[i];
		if (amd_iommu_rlookup_table[bdf] == iommu)
			return 1;
	}

	return 0;
}