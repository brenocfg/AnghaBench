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

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char const*) ; 

__attribute__((used)) static inline int comedi_pci_enable(struct pci_dev *pdev, const char *res_name)
{
	int rc;

	rc = pci_enable_device(pdev);
	if (rc < 0)
		return rc;

	rc = pci_request_regions(pdev, res_name);
	if (rc < 0)
		pci_disable_device(pdev);

	return rc;
}