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
 int /*<<< orphan*/  pci_ats_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_ats (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_disable_dev_iotlb(struct device_domain_info *info)
{
	if (!info->dev || !pci_ats_enabled(info->dev))
		return;

	pci_disable_ats(info->dev);
}