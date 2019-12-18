#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_domain_info* iommu; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct dmar_domain {int dummy; } ;
struct device_domain_info {struct dmar_domain* domain; } ;

/* Variables and functions */

__attribute__((used)) static struct dmar_domain *
find_domain(struct pci_dev *pdev)
{
	struct device_domain_info *info;

	/* No lock here, assumes no domain exit in normal case */
	info = pdev->dev.archdata.iommu;
	if (info)
		return info->domain;
	return NULL;
}