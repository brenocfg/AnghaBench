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
struct beiscsi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  beiscsi_quiesce (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void beiscsi_shutdown(struct pci_dev *pcidev)
{

	struct beiscsi_hba *phba = NULL;

	phba = (struct beiscsi_hba *)pci_get_drvdata(pcidev);
	if (!phba) {
		dev_err(&pcidev->dev, "beiscsi_shutdown called with no phba\n");
		return;
	}

	beiscsi_quiesce(phba);
	pci_disable_device(pcidev);
}