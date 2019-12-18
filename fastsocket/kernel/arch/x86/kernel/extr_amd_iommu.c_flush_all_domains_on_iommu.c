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
 int MAX_DOMAIN_ID ; 
 int /*<<< orphan*/  amd_iommu_pd_alloc_bitmap ; 
 int /*<<< orphan*/  flush_domain_on_iommu (struct amd_iommu*,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_all_domains_on_iommu(struct amd_iommu *iommu)
{
	int i;

	for (i = 1; i < MAX_DOMAIN_ID; ++i) {
		if (!test_bit(i, amd_iommu_pd_alloc_bitmap))
			continue;
		flush_domain_on_iommu(iommu, i);
	}

}