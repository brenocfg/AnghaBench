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
struct iotlb_lock {scalar_t__ vict; scalar_t__ base; } ;
struct iommu {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_GFLUSH ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_write_reg (struct iommu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iotlb_lock_set (struct iommu*,struct iotlb_lock*) ; 

void flush_iotlb_all(struct iommu *obj)
{
	struct iotlb_lock l;

	clk_enable(obj->clk);

	l.base = 0;
	l.vict = 0;
	iotlb_lock_set(obj, &l);

	iommu_write_reg(obj, 1, MMU_GFLUSH);

	clk_disable(obj->clk);
}