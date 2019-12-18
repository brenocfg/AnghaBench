#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; TYPE_1__* subordinate; } ;
struct dmar_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; struct pci_dev* self; } ;

/* Variables and functions */
 int domain_context_mapping_one (struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 struct pci_dev* pci_find_upstream_pcie_bridge (struct pci_dev*) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 

__attribute__((used)) static int
domain_context_mapping(struct dmar_domain *domain, struct pci_dev *pdev,
			int translation)
{
	int ret;
	struct pci_dev *tmp, *parent;

	ret = domain_context_mapping_one(domain, pci_domain_nr(pdev->bus),
					 pdev->bus->number, pdev->devfn,
					 translation);
	if (ret)
		return ret;

	/* dependent device mapping */
	tmp = pci_find_upstream_pcie_bridge(pdev);
	if (!tmp)
		return 0;
	/* Secondary interface's bus number and devfn 0 */
	parent = pdev->bus->self;
	while (parent != tmp) {
		ret = domain_context_mapping_one(domain,
						 pci_domain_nr(parent->bus),
						 parent->bus->number,
						 parent->devfn, translation);
		if (ret)
			return ret;
		parent = parent->bus->self;
	}
	if (pci_is_pcie(tmp)) /* this is a PCIe-to-PCI bridge */
		return domain_context_mapping_one(domain,
					pci_domain_nr(tmp->subordinate),
					tmp->subordinate->number, 0,
					translation);
	else /* this is a legacy PCI bridge */
		return domain_context_mapping_one(domain,
						  pci_domain_nr(tmp->bus),
						  tmp->bus->number,
						  tmp->devfn,
						  translation);
}