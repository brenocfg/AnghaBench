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
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* subordinate; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int bus_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int PCI_BUS_FLAGS_NO_MSI ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t
msi_bus_store(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	unsigned long val;

	if (strict_strtoul(buf, 0, &val) < 0)
		return -EINVAL;

	/* bad things may happen if the no_msi flag is changed
	 * while some drivers are loaded */
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	/* Maybe pci devices without subordinate busses shouldn't even have this
	 * attribute in the first place?  */
	if (!pdev->subordinate)
		return count;

	/* Is the flag going to change, or keep the value it already had? */
	if (!(pdev->subordinate->bus_flags & PCI_BUS_FLAGS_NO_MSI) ^
	    !!val) {
		pdev->subordinate->bus_flags ^= PCI_BUS_FLAGS_NO_MSI;

		dev_warn(&pdev->dev, "forced subordinate bus to%s support MSI,"
			 " bad things could happen\n", val ? "" : " not");
	}

	return count;
}