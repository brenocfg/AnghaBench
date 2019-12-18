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
struct pci_dev {TYPE_1__* resource; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IORESOURCE_ROM_SHADOW ; 
 size_t PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 struct pci_dev* vga_default_device () ; 

__attribute__((used)) static ssize_t
boot_vga_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct pci_dev *vga_dev = vga_default_device();

	if (vga_dev)
		return sprintf(buf, "%u\n", (pdev == vga_dev));

	return sprintf(buf, "%u\n",
		!!(pdev->resource[PCI_ROM_RESOURCE].flags &
		   IORESOURCE_ROM_SHADOW));
}