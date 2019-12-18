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
struct bnx2i_hba {int /*<<< orphan*/ * regview; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  ep_destroy_list; int /*<<< orphan*/  ep_active_list; int /*<<< orphan*/  ep_ofld_list; struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2i_free_mp_bdt (struct bnx2i_hba*) ; 
 int /*<<< orphan*/  bnx2i_release_free_cid_que (struct bnx2i_hba*) ; 
 int /*<<< orphan*/  iscsi_host_free (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_host_remove (struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnx2i_free_hba(struct bnx2i_hba *hba)
{
	struct Scsi_Host *shost = hba->shost;

	iscsi_host_remove(shost);
	INIT_LIST_HEAD(&hba->ep_ofld_list);
	INIT_LIST_HEAD(&hba->ep_active_list);
	INIT_LIST_HEAD(&hba->ep_destroy_list);
	pci_dev_put(hba->pcidev);

	if (hba->regview) {
		pci_iounmap(hba->pcidev, hba->regview);
		hba->regview = NULL;
	}
	bnx2i_free_mp_bdt(hba);
	bnx2i_release_free_cid_que(hba);
	iscsi_host_free(shost);
}