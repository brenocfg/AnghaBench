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
typedef  int /*<<< orphan*/  u32 ;
struct iotlb_lock {int /*<<< orphan*/  base; int /*<<< orphan*/  vict; } ;
struct iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MMU_LOCK ; 
 int /*<<< orphan*/  MMU_LOCK_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_LOCK_VICT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_read_reg (struct iommu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iotlb_lock_get(struct iommu *obj, struct iotlb_lock *l)
{
	u32 val;

	val = iommu_read_reg(obj, MMU_LOCK);

	l->base = MMU_LOCK_BASE(val);
	l->vict = MMU_LOCK_VICT(val);

	BUG_ON(l->base != 0); /* Currently no preservation is used */
}