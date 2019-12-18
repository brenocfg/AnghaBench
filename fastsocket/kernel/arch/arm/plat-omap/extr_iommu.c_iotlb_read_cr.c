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
struct iommu {int dummy; } ;
struct cr_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tlb_read_cr ) (struct iommu*,struct cr_regs*) ;} ;

/* Variables and functions */
 TYPE_1__* arch_iommu ; 
 int /*<<< orphan*/  stub1 (struct iommu*,struct cr_regs*) ; 

__attribute__((used)) static void iotlb_read_cr(struct iommu *obj, struct cr_regs *cr)
{
	arch_iommu->tlb_read_cr(obj, cr);
}