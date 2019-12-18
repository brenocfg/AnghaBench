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
struct device_node {char* full_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t pci_show_devspec(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct pci_dev *pdev;
	struct device_node *np;

	pdev = to_pci_dev (dev);
	np = pci_device_to_OF_node(pdev);
	if (np == NULL || np->full_name == NULL)
		return 0;
	return sprintf(buf, "%s", np->full_name);
}