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
struct bfad_s {int /*<<< orphan*/  pci_bar2_kva; int /*<<< orphan*/  pci_bar0_kva; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

void
bfad_pci_uninit(struct pci_dev *pdev, struct bfad_s *bfad)
{
	pci_iounmap(pdev, bfad->pci_bar0_kva);
	pci_iounmap(pdev, bfad->pci_bar2_kva);
	pci_release_regions(pdev);
	/* Disable PCIE Advanced Error Recovery (AER) */
	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}