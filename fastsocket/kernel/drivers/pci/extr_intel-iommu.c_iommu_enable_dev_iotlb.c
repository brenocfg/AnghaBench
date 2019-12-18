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
struct device_domain_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTD_PAGE_SHIFT ; 
 int /*<<< orphan*/  pci_enable_ats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_enable_dev_iotlb(struct device_domain_info *info)
{
	if (!info)
		return;

	pci_enable_ats(info->dev, VTD_PAGE_SHIFT);
}