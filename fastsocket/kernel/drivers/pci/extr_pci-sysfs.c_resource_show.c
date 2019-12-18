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
struct resource {scalar_t__ flags; } ;
struct pci_dev {struct resource* resource; scalar_t__ subordinate; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int DEVICE_COUNT_RESOURCE ; 
 int PCI_BRIDGE_RESOURCES ; 
 int /*<<< orphan*/  pci_resource_to_user (struct pci_dev*,int,struct resource*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long,unsigned long long,unsigned long long) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t
resource_show(struct device * dev, struct device_attribute *attr, char * buf)
{
	struct pci_dev * pci_dev = to_pci_dev(dev);
	char * str = buf;
	int i;
	int max;
	resource_size_t start, end;

	if (pci_dev->subordinate)
		max = DEVICE_COUNT_RESOURCE;
	else
		max = PCI_BRIDGE_RESOURCES;

	for (i = 0; i < max; i++) {
		struct resource *res =  &pci_dev->resource[i];
		pci_resource_to_user(pci_dev, i, res, &start, &end);
		str += sprintf(str,"0x%016llx 0x%016llx 0x%016llx\n",
			       (unsigned long long)start,
			       (unsigned long long)end,
			       (unsigned long long)res->flags);
	}
	return (str - buf);
}