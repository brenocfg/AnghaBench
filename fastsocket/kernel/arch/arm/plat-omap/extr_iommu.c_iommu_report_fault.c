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
typedef  int /*<<< orphan*/  u32 ;
struct iommu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fault_isr ) (struct iommu*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* arch_iommu ; 
 int /*<<< orphan*/  stub1 (struct iommu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 iommu_report_fault(struct iommu *obj, u32 *da)
{
	return arch_iommu->fault_isr(obj, da);
}