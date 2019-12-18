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
struct pci_dn {struct device_node* node; } ;
struct pci_dev {int dummy; } ;
struct device_node {int full_name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOSPC ; 
 struct pci_dn* get_pdn (struct pci_dev*) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 

__attribute__((used)) static int check_req(struct pci_dev *pdev, int nvec, char *prop_name)
{
	struct device_node *dn;
	struct pci_dn *pdn;
	const u32 *req_msi;

	pdn = get_pdn(pdev);
	if (!pdn)
		return -ENODEV;

	dn = pdn->node;

	req_msi = of_get_property(dn, prop_name, NULL);
	if (!req_msi) {
		pr_debug("rtas_msi: No %s on %s\n", prop_name, dn->full_name);
		return -ENOENT;
	}

	if (*req_msi < nvec) {
		pr_debug("rtas_msi: %s requests < %d MSIs\n", prop_name, nvec);

		if (*req_msi == 0) /* Be paranoid */
			return -ENOSPC;

		return *req_msi;
	}

	return 0;
}