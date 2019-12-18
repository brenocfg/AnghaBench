#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {scalar_t__ chip_id; int number_of_intr; int /*<<< orphan*/  shost; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  name; } ;
struct pci_dev {int /*<<< orphan*/  current_state; } ;
struct TYPE_2__ {int (* chip_init ) (struct pm8001_hba_info*) ;int /*<<< orphan*/  (* interrupt_enable ) (struct pm8001_hba_info*,int) ;int /*<<< orphan*/  (* interrupt_disable ) (struct pm8001_hba_info*,int) ;int /*<<< orphan*/  (* chip_soft_rst ) (struct pm8001_hba_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 TYPE_1__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ chip_8001 ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 int pci_go_44 (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int pm8001_request_irq (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  pm8001_tasklet ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*) ; 
 int stub2 (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  stub3 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub4 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub5 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int pm8001_pci_resume(struct pci_dev *pdev)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct pm8001_hba_info *pm8001_ha;
	int rc;
	u8 i = 0;
	u32 device_state;
	pm8001_ha = sha->lldd_ha;
	device_state = pdev->current_state;

	pm8001_printk("pdev=0x%p, slot=%s, resuming from previous "
		"operating state [D%d]\n", pdev, pm8001_ha->name, device_state);

	pci_set_power_state(pdev, PCI_D0);
	pci_enable_wake(pdev, PCI_D0, 0);
	pci_restore_state(pdev);
	rc = pci_enable_device(pdev);
	if (rc) {
		pm8001_printk("slot=%s Enable device failed during resume\n",
			      pm8001_ha->name);
		goto err_out_enable;
	}

	pci_set_master(pdev);
	rc = pci_go_44(pdev);
	if (rc)
		goto err_out_disable;

	/* chip soft rst only for spc */
	if (pm8001_ha->chip_id == chip_8001) {
		PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("chip soft reset successful\n"));
	}
	rc = PM8001_CHIP_DISP->chip_init(pm8001_ha);
	if (rc)
		goto err_out_disable;

	/* disable all the interrupt bits */
	PM8001_CHIP_DISP->interrupt_disable(pm8001_ha, 0xFF);

	rc = pm8001_request_irq(pm8001_ha);
	if (rc)
		goto err_out_disable;
#ifdef PM8001_USE_TASKLET
	/* default tasklet for non msi-x interrupt handler/first msi-x
	* interrupt handler */
	tasklet_init(&pm8001_ha->tasklet, pm8001_tasklet,
			(unsigned long)pm8001_ha);
#endif
	PM8001_CHIP_DISP->interrupt_enable(pm8001_ha, 0);
	if (pm8001_ha->chip_id != chip_8001) {
		for (i = 1; i < pm8001_ha->number_of_intr; i++)
			PM8001_CHIP_DISP->interrupt_enable(pm8001_ha, i);
	}
	scsi_unblock_requests(pm8001_ha->shost);
	return 0;

err_out_disable:
	scsi_remove_host(pm8001_ha->shost);
	pci_disable_device(pdev);
err_out_enable:
	return rc;
}