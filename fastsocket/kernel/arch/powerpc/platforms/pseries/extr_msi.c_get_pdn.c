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
struct pci_dn {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 

__attribute__((used)) static struct pci_dn *get_pdn(struct pci_dev *pdev)
{
	struct device_node *dn;
	struct pci_dn *pdn;

	dn = pci_device_to_OF_node(pdev);
	if (!dn) {
		dev_dbg(&pdev->dev, "rtas_msi: No OF device node\n");
		return NULL;
	}

	pdn = PCI_DN(dn);
	if (!pdn) {
		dev_dbg(&pdev->dev, "rtas_msi: No PCI DN\n");
		return NULL;
	}

	return pdn;
}