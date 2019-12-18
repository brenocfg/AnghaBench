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
struct TYPE_2__ {int /*<<< orphan*/  (* unmap ) (struct iommu_domain*,unsigned long,size_t) ;} ;

/* Variables and functions */
 TYPE_1__* iommu_ops ; 
 int /*<<< orphan*/  stub1 (struct iommu_domain*,unsigned long,size_t) ; 

void iommu_unmap_range(struct iommu_domain *domain, unsigned long iova,
		      size_t size)
{
	iommu_ops->unmap(domain, iova, size);
}