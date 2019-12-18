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
typedef  size_t u16 ;
struct protection_domain {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct notifier_block {int dummy; } ;
struct dma_ops_domain {size_t target_dev; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dma_ops; } ;
struct device {TYPE_2__ archdata; } ;
struct amd_iommu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 129 
#define  BUS_NOTIFY_UNBOUND_DRIVER 128 
 size_t* amd_iommu_alias_table ; 
 int /*<<< orphan*/  amd_iommu_dma_ops ; 
 size_t amd_iommu_last_bdf ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  attach_device (struct amd_iommu*,int /*<<< orphan*/ ,size_t) ; 
 size_t calc_devid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_device (struct protection_domain*,size_t) ; 
 struct dma_ops_domain* dma_ops_domain_alloc (struct amd_iommu*) ; 
 struct protection_domain* domain_for_device (size_t) ; 
 struct dma_ops_domain* find_protection_domain (size_t) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_pass_through ; 
 int /*<<< orphan*/  iommu_pd_list ; 
 int /*<<< orphan*/  iommu_pd_list_lock ; 
 int /*<<< orphan*/  iommu_queue_inv_dev_entry (struct amd_iommu*,size_t) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_domain ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int device_change_notifier(struct notifier_block *nb,
				  unsigned long action, void *data)
{
	struct device *dev = data;
	struct pci_dev *pdev = to_pci_dev(dev);
	u16 devid = calc_devid(pdev->bus->number, pdev->devfn);
	struct protection_domain *domain;
	struct dma_ops_domain *dma_domain;
	struct amd_iommu *iommu;
	unsigned long flags;

	if (devid > amd_iommu_last_bdf)
		goto out;

	devid = amd_iommu_alias_table[devid];

	iommu = amd_iommu_rlookup_table[devid];
	if (iommu == NULL)
		goto out;

	domain = domain_for_device(devid);

	switch (action) {
	case BUS_NOTIFY_UNBOUND_DRIVER:
		if (!domain)
			goto out;
		if (iommu_pass_through)
			break;
		detach_device(domain, devid);
		break;
	case BUS_NOTIFY_ADD_DEVICE:

		if (iommu_pass_through) {
			attach_device(iommu, pt_domain, devid);
			break;
		}

		/* allocate a protection domain if a device is added */
		dma_domain = find_protection_domain(devid);
		if (dma_domain)
			goto out;
		dma_domain = dma_ops_domain_alloc(iommu);
		if (!dma_domain)
			goto out;
		dma_domain->target_dev = devid;

		spin_lock_irqsave(&iommu_pd_list_lock, flags);
		list_add_tail(&dma_domain->list, &iommu_pd_list);
		spin_unlock_irqrestore(&iommu_pd_list_lock, flags);

		dev->archdata.dma_ops = &amd_iommu_dma_ops;

		break;
	default:
		goto out;
	}

	iommu_queue_inv_dev_entry(iommu, devid);
	iommu_completion_wait(iommu);

out:
	return 0;
}