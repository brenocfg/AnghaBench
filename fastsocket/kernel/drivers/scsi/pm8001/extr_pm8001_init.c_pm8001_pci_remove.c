#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_ha_struct {struct sas_ha_struct* sas_port; struct sas_ha_struct* sas_phy; struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {int number_of_intr; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; struct sas_ha_struct* outq; TYPE_1__* msix_entries; int /*<<< orphan*/  shost; int /*<<< orphan*/  list; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* chip_soft_rst ) (struct pm8001_hba_info*) ;int /*<<< orphan*/  (* interrupt_disable ) (struct pm8001_hba_info*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 TYPE_2__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sas_ha_struct*) ; 
 int /*<<< orphan*/  kfree (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm8001_free (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  sas_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_unregister_ha (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pm8001_pci_remove(struct pci_dev *pdev)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct pm8001_hba_info *pm8001_ha;
	int i;
	pm8001_ha = sha->lldd_ha;
	pci_set_drvdata(pdev, NULL);
	sas_unregister_ha(sha);
	sas_remove_host(pm8001_ha->shost);
	list_del(&pm8001_ha->list);
	scsi_remove_host(pm8001_ha->shost);
	PM8001_CHIP_DISP->interrupt_disable(pm8001_ha, 0xFF);
	PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);

#ifdef PM8001_USE_MSIX
	for (i = 0; i < pm8001_ha->number_of_intr; i++)
		synchronize_irq(pm8001_ha->msix_entries[i].vector);
	for (i = 0; i < pm8001_ha->number_of_intr; i++)
		free_irq(pm8001_ha->msix_entries[i].vector,
				&pm8001_ha->outq[i]);
	pci_disable_msix(pdev);
#else
	free_irq(pm8001_ha->irq, sha);
#endif
#ifdef PM8001_USE_TASKLET
	tasklet_kill(&pm8001_ha->tasklet);
#endif
	pm8001_free(pm8001_ha);
	kfree(sha->sas_phy);
	kfree(sha->sas_port);
	kfree(sha);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}