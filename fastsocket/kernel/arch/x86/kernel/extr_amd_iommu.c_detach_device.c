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
typedef  int /*<<< orphan*/  u16 ;
struct protection_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __detach_device (struct protection_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_devtable_lock ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void detach_device(struct protection_domain *domain, u16 devid)
{
	unsigned long flags;

	/* lock device table */
	write_lock_irqsave(&amd_iommu_devtable_lock, flags);
	__detach_device(domain, devid);
	write_unlock_irqrestore(&amd_iommu_devtable_lock, flags);
}