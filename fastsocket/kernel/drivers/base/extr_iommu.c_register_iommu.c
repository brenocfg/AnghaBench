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
struct iommu_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct iommu_ops* iommu_ops ; 

void register_iommu(struct iommu_ops *ops)
{
	if (iommu_ops)
		BUG();

	iommu_ops = ops;
}