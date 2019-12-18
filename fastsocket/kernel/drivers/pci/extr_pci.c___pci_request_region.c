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
struct pci_devres {int region_mask; } ;
struct pci_dev {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  __request_mem_region (int /*<<< orphan*/ ,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 struct pci_devres* find_pci_dr (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,scalar_t__,char const*) ; 

__attribute__((used)) static int __pci_request_region(struct pci_dev *pdev, int bar, const char *res_name,
									int exclusive)
{
	struct pci_devres *dr;

	if (pci_resource_len(pdev, bar) == 0)
		return 0;
		
	if (pci_resource_flags(pdev, bar) & IORESOURCE_IO) {
		if (!request_region(pci_resource_start(pdev, bar),
			    pci_resource_len(pdev, bar), res_name))
			goto err_out;
	}
	else if (pci_resource_flags(pdev, bar) & IORESOURCE_MEM) {
		if (!__request_mem_region(pci_resource_start(pdev, bar),
					pci_resource_len(pdev, bar), res_name,
					exclusive))
			goto err_out;
	}

	dr = find_pci_dr(pdev);
	if (dr)
		dr->region_mask |= 1 << bar;

	return 0;

err_out:
	dev_warn(&pdev->dev, "BAR %d: can't reserve %pR\n", bar,
		 &pdev->resource[bar]);
	return -EBUSY;
}