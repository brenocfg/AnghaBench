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
struct iommu_functions {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct iommu_functions const* arch_iommu ; 

int install_iommu_arch(const struct iommu_functions *ops)
{
	if (arch_iommu)
		return -EBUSY;

	arch_iommu = ops;
	return 0;
}