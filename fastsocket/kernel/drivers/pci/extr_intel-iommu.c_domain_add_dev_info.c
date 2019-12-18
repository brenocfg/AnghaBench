#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_domain_info* iommu; } ;
struct TYPE_5__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; int /*<<< orphan*/  devfn; TYPE_3__* bus; } ;
struct dmar_domain {int /*<<< orphan*/  devices; } ;
struct device_domain_info {int /*<<< orphan*/  global; int /*<<< orphan*/  link; struct dmar_domain* domain; struct pci_dev* dev; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  segment; } ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct device_domain_info* alloc_devinfo_mem () ; 
 int /*<<< orphan*/  device_domain_list ; 
 int /*<<< orphan*/  device_domain_lock ; 
 int domain_context_mapping (struct dmar_domain*,struct pci_dev*,int) ; 
 int /*<<< orphan*/  free_devinfo_mem (struct device_domain_info*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlink_domain_info (struct device_domain_info*) ; 

__attribute__((used)) static int domain_add_dev_info(struct dmar_domain *domain,
			       struct pci_dev *pdev,
			       int translation)
{
	struct device_domain_info *info;
	unsigned long flags;
	int ret;

	info = alloc_devinfo_mem();
	if (!info)
		return -ENOMEM;

	info->segment = pci_domain_nr(pdev->bus);
	info->bus = pdev->bus->number;
	info->devfn = pdev->devfn;
	info->dev = pdev;
	info->domain = domain;

	spin_lock_irqsave(&device_domain_lock, flags);
	list_add(&info->link, &domain->devices);
	list_add(&info->global, &device_domain_list);
	pdev->dev.archdata.iommu = info;
	spin_unlock_irqrestore(&device_domain_lock, flags);

	ret = domain_context_mapping(domain, pdev, translation);
	if (ret) {
		spin_lock_irqsave(&device_domain_lock, flags);
		unlink_domain_info(info);
		spin_unlock_irqrestore(&device_domain_lock, flags);
		free_devinfo_mem(info);
		return ret;
	}

	return 0;
}