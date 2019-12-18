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
struct amd_iommu {unsigned long cap; } ;

/* Variables and functions */
 unsigned long IOMMU_CAP_NPCACHE ; 

__attribute__((used)) static int iommu_has_npcache(struct amd_iommu *iommu)
{
	return iommu->cap & (1UL << IOMMU_CAP_NPCACHE);
}