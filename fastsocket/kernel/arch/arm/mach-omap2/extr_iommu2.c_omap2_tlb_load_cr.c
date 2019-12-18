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
struct iommu {int dummy; } ;
struct cr_regs {int cam; int ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_CAM ; 
 int MMU_CAM_V ; 
 int /*<<< orphan*/  MMU_RAM ; 
 int /*<<< orphan*/  iommu_write_reg (struct iommu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_tlb_load_cr(struct iommu *obj, struct cr_regs *cr)
{
	iommu_write_reg(obj, cr->cam | MMU_CAM_V, MMU_CAM);
	iommu_write_reg(obj, cr->ram, MMU_RAM);
}