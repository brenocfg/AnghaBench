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
struct beiscsi_hba {int /*<<< orphan*/  shost; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  boot_kset; } ;

/* Variables and functions */
 int /*<<< orphan*/  beiscsi_destroy_def_ifaces (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_quiesce (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct beiscsi_hba* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void beiscsi_remove(struct pci_dev *pcidev)
{

	struct beiscsi_hba *phba = NULL;

	phba = pci_get_drvdata(pcidev);
	if (!phba) {
		dev_err(&pcidev->dev, "beiscsi_remove called with no phba\n");
		return;
	}

	beiscsi_destroy_def_ifaces(phba);
	beiscsi_quiesce(phba);
	iscsi_boot_destroy_kset(phba->boot_kset);
	iscsi_host_remove(phba->shost);
	pci_dev_put(phba->pcidev);
	iscsi_host_free(phba->shost);
	pci_disable_device(pcidev);
}