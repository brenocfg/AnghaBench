#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int (* map ) (struct iommu_domain*,unsigned long,int /*<<< orphan*/ ,size_t,int) ;} ;

/* Variables and functions */
 TYPE_1__* iommu_ops ; 
 int stub1 (struct iommu_domain*,unsigned long,int /*<<< orphan*/ ,size_t,int) ; 

int iommu_map_range(struct iommu_domain *domain, unsigned long iova,
		    phys_addr_t paddr, size_t size, int prot)
{
	return iommu_ops->map(domain, iova, paddr, size, prot);
}