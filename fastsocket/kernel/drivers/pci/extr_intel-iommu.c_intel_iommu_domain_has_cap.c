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
struct iommu_domain {struct dmar_domain* priv; } ;
struct dmar_domain {int iommu_snooping; } ;

/* Variables and functions */
 unsigned long IOMMU_CAP_CACHE_COHERENCY ; 
 unsigned long IOMMU_CAP_INTR_REMAP ; 
 int intr_remapping_enabled ; 

__attribute__((used)) static int intel_iommu_domain_has_cap(struct iommu_domain *domain,
				      unsigned long cap)
{
	struct dmar_domain *dmar_domain = domain->priv;

	if (cap == IOMMU_CAP_CACHE_COHERENCY)
		return dmar_domain->iommu_snooping;
	if (cap == IOMMU_CAP_INTR_REMAP)
		return intr_remapping_enabled;

	return 0;
}