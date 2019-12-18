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
typedef  size_t u16 ;
struct protection_domain {int /*<<< orphan*/  id; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct dma_ops_domain {struct protection_domain domain; } ;
struct device {int /*<<< orphan*/ * bus; } ;
struct amd_iommu {struct dma_ops_domain* default_dom; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t* amd_iommu_alias_table ; 
 size_t amd_iommu_last_bdf ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  attach_device (struct amd_iommu*,struct protection_domain*,size_t) ; 
 size_t calc_devid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct protection_domain* domain_for_device (size_t) ; 
 struct dma_ops_domain* find_protection_domain (size_t) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int get_device_resources(struct device *dev,
				struct amd_iommu **iommu,
				struct protection_domain **domain,
				u16 *bdf)
{
	struct dma_ops_domain *dma_dom;
	struct pci_dev *pcidev;
	u16 _bdf;

	*iommu = NULL;
	*domain = NULL;
	*bdf = 0xffff;

	if (dev->bus != &pci_bus_type)
		return 0;

	pcidev = to_pci_dev(dev);
	_bdf = calc_devid(pcidev->bus->number, pcidev->devfn);

	/* device not translated by any IOMMU in the system? */
	if (_bdf > amd_iommu_last_bdf)
		return 0;

	*bdf = amd_iommu_alias_table[_bdf];

	*iommu = amd_iommu_rlookup_table[*bdf];
	if (*iommu == NULL)
		return 0;
	*domain = domain_for_device(*bdf);
	if (*domain == NULL) {
		dma_dom = find_protection_domain(*bdf);
		if (!dma_dom)
			dma_dom = (*iommu)->default_dom;
		*domain = &dma_dom->domain;
		attach_device(*iommu, *domain, *bdf);
		DUMP_printk("Using protection domain %d for device %s\n",
			    (*domain)->id, dev_name(dev));
	}

	if (domain_for_device(_bdf) == NULL)
		attach_device(*iommu, *domain, _bdf);

	return 1;
}