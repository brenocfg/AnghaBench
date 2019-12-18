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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct irq_host {struct axon_msic* host_data; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;
struct axon_msic {int dummy; } ;
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct irq_host* irq_find_host (struct device_node*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/  const) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pci_device_to_OF_node (struct pci_dev*) ; 

__attribute__((used)) static struct axon_msic *find_msi_translator(struct pci_dev *dev)
{
	struct irq_host *irq_host;
	struct device_node *dn, *tmp;
	const phandle *ph;
	struct axon_msic *msic = NULL;

	dn = of_node_get(pci_device_to_OF_node(dev));
	if (!dn) {
		dev_dbg(&dev->dev, "axon_msi: no pci_dn found\n");
		return NULL;
	}

	for (; dn; dn = of_get_next_parent(dn)) {
		ph = of_get_property(dn, "msi-translator", NULL);
		if (ph)
			break;
	}

	if (!ph) {
		dev_dbg(&dev->dev,
			"axon_msi: no msi-translator property found\n");
		goto out_error;
	}

	tmp = dn;
	dn = of_find_node_by_phandle(*ph);
	of_node_put(tmp);
	if (!dn) {
		dev_dbg(&dev->dev,
			"axon_msi: msi-translator doesn't point to a node\n");
		goto out_error;
	}

	irq_host = irq_find_host(dn);
	if (!irq_host) {
		dev_dbg(&dev->dev, "axon_msi: no irq_host found for node %s\n",
			dn->full_name);
		goto out_error;
	}

	msic = irq_host->host_data;

out_error:
	of_node_put(dn);

	return msic;
}