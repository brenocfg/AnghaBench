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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device_node *find_pe_total_msi(struct pci_dev *dev, int *total)
{
	struct device_node *dn;
	const u32 *p;

	dn = of_node_get(pci_device_to_OF_node(dev));
	while (dn) {
		p = of_get_property(dn, "ibm,pe-total-#msi", NULL);
		if (p) {
			pr_debug("rtas_msi: found prop on dn %s\n",
				dn->full_name);
			*total = *p;
			return dn;
		}

		dn = of_get_next_parent(dn);
	}

	return NULL;
}