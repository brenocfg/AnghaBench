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
struct lpfc_vport {int dummy; } ;
struct lpfc_hba {TYPE_1__* pcidev; struct lpfc_vport* pport; int /*<<< orphan*/  brd_no; int /*<<< orphan*/  sdev_cnt; int /*<<< orphan*/  fc_arbtov; int /*<<< orphan*/  fc_altov; int /*<<< orphan*/  fc_ratov; int /*<<< orphan*/  fc_edtov; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FF_DEF_ALTOV ; 
 int /*<<< orphan*/  FF_DEF_ARBTOV ; 
 int /*<<< orphan*/  FF_DEF_EDTOV ; 
 int /*<<< orphan*/  FF_DEF_RATOV ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct lpfc_vport* lpfc_create_port (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_initialize (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_1__*,struct Scsi_Host*) ; 

__attribute__((used)) static int
lpfc_create_shost(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport;
	struct Scsi_Host  *shost;

	/* Initialize HBA FC structure */
	phba->fc_edtov = FF_DEF_EDTOV;
	phba->fc_ratov = FF_DEF_RATOV;
	phba->fc_altov = FF_DEF_ALTOV;
	phba->fc_arbtov = FF_DEF_ARBTOV;

	atomic_set(&phba->sdev_cnt, 0);
	vport = lpfc_create_port(phba, phba->brd_no, &phba->pcidev->dev);
	if (!vport)
		return -ENODEV;

	shost = lpfc_shost_from_vport(vport);
	phba->pport = vport;
	lpfc_debugfs_initialize(vport);
	/* Put reference to SCSI host to driver's device private data */
	pci_set_drvdata(phba->pcidev, shost);

	return 0;
}