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
typedef  size_t uint16_t ;
struct iscsi_wrb {int dummy; } ;
struct iscsi_task {struct beiscsi_io_task* dd_data; } ;
struct hwi_wrb_context {int dummy; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct beiscsi_io_task {int /*<<< orphan*/  mtask_data_count; scalar_t__ mtask_addr; int /*<<< orphan*/ * psgl_handle; TYPE_1__* pwrb_handle; } ;
struct beiscsi_hba {int /*<<< orphan*/  pcidev; int /*<<< orphan*/  mgmt_sgl_lock; struct hwi_controller* phwi_ctrlr; } ;
struct beiscsi_conn {int /*<<< orphan*/  beiscsi_conn_cid; struct beiscsi_hba* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwrb; } ;

/* Variables and functions */
 size_t BE_GET_CRI_FROM_CID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  free_mgmt_sgl_handle (struct beiscsi_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_wrb_handle (struct beiscsi_hba*,struct hwi_wrb_context*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
beiscsi_free_mgmt_task_handles(struct beiscsi_conn *beiscsi_conn,
				struct iscsi_task *task)
{
	struct beiscsi_io_task *io_task;
	struct beiscsi_hba *phba = beiscsi_conn->phba;
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	uint16_t cri_index = BE_GET_CRI_FROM_CID(
				beiscsi_conn->beiscsi_conn_cid);

	phwi_ctrlr = phba->phwi_ctrlr;
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];

	io_task = task->dd_data;

	if (io_task->pwrb_handle) {
		memset(io_task->pwrb_handle->pwrb, 0,
		       sizeof(struct iscsi_wrb));
		free_wrb_handle(phba, pwrb_context,
				io_task->pwrb_handle);
		io_task->pwrb_handle = NULL;
	}

	if (io_task->psgl_handle) {
		spin_lock_bh(&phba->mgmt_sgl_lock);
		free_mgmt_sgl_handle(phba,
				     io_task->psgl_handle);
		io_task->psgl_handle = NULL;
		spin_unlock_bh(&phba->mgmt_sgl_lock);
	}

	if (io_task->mtask_addr)
		pci_unmap_single(phba->pcidev,
				 io_task->mtask_addr,
				 io_task->mtask_data_count,
				 PCI_DMA_TODEVICE);
}