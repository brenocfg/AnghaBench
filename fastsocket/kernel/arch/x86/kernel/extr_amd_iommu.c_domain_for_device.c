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
typedef  size_t u16 ;
struct protection_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_devtable_lock ; 
 struct protection_domain** amd_iommu_pd_table ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct protection_domain *domain_for_device(u16 devid)
{
	struct protection_domain *dom;
	unsigned long flags;

	read_lock_irqsave(&amd_iommu_devtable_lock, flags);
	dom = amd_iommu_pd_table[devid];
	read_unlock_irqrestore(&amd_iommu_devtable_lock, flags);

	return dom;
}