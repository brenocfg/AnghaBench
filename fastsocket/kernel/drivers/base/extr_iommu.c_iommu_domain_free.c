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
struct TYPE_2__ {int /*<<< orphan*/  (* domain_destroy ) (struct iommu_domain*) ;} ;

/* Variables and functions */
 TYPE_1__* iommu_ops ; 
 int /*<<< orphan*/  kfree (struct iommu_domain*) ; 
 int /*<<< orphan*/  stub1 (struct iommu_domain*) ; 

void iommu_domain_free(struct iommu_domain *domain)
{
	iommu_ops->domain_destroy(domain);
	kfree(domain);
}