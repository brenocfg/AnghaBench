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
struct pci_dev {int dummy; } ;
struct iommu_domain {struct dmar_domain* priv; } ;
struct dmar_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_remove_one_dev_info (struct dmar_domain*,struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void intel_iommu_detach_device(struct iommu_domain *domain,
				      struct device *dev)
{
	struct dmar_domain *dmar_domain = domain->priv;
	struct pci_dev *pdev = to_pci_dev(dev);

	domain_remove_one_dev_info(dmar_domain, pdev);
}