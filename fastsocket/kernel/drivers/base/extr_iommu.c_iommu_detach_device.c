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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach_dev ) (struct iommu_domain*,struct device*) ;} ;

/* Variables and functions */
 TYPE_1__* iommu_ops ; 
 int /*<<< orphan*/  stub1 (struct iommu_domain*,struct device*) ; 

void iommu_detach_device(struct iommu_domain *domain, struct device *dev)
{
	iommu_ops->detach_dev(domain, dev);
}