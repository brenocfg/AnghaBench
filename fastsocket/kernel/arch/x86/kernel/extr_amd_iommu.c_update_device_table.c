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
struct protection_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_devtable_lock ; 
 int amd_iommu_last_bdf ; 
 struct protection_domain** amd_iommu_pd_table ; 
 int /*<<< orphan*/  set_dte_entry (int,struct protection_domain*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void update_device_table(struct protection_domain *domain)
{
	unsigned long flags;
	int i;

	for (i = 0; i <= amd_iommu_last_bdf; ++i) {
		if (amd_iommu_pd_table[i] != domain)
			continue;
		write_lock_irqsave(&amd_iommu_devtable_lock, flags);
		set_dte_entry(i, domain);
		write_unlock_irqrestore(&amd_iommu_devtable_lock, flags);
	}
}