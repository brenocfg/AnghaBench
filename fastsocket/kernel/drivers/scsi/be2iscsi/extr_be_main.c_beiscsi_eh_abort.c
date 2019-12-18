#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ptr; } ;
struct scsi_cmnd {int /*<<< orphan*/  device; TYPE_1__ SCp; } ;
struct iscsi_task {struct iscsi_conn* conn; struct beiscsi_io_task* dd_data; int /*<<< orphan*/  sc; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_conn {struct beiscsi_conn* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct invalidate_commands_params_in {int dummy; } ;
struct invalidate_command_table {unsigned int cid; int /*<<< orphan*/  icd; } ;
struct beiscsi_io_task {TYPE_2__* psgl_handle; int /*<<< orphan*/  scsi_cmnd; } ;
struct TYPE_6__ {int /*<<< orphan*/  pdev; } ;
struct beiscsi_hba {TYPE_3__ ctrl; struct invalidate_command_table* inv_tbl; } ;
struct beiscsi_conn {unsigned int beiscsi_conn_cid; struct beiscsi_hba* phba; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; int /*<<< orphan*/ * va; } ;
struct TYPE_5__ {int /*<<< orphan*/  sgl_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_EH ; 
 int FAILED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SUCCESS ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iscsi_eh_abort (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  memset (struct invalidate_command_table*,int,int) ; 
 unsigned int mgmt_invalidate_icds (struct beiscsi_hba*,struct invalidate_command_table*,unsigned int,unsigned int,struct be_dma_mem*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct iscsi_cls_session* starget_to_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_eh_abort(struct scsi_cmnd *sc)
{
	struct iscsi_cls_session *cls_session;
	struct iscsi_task *aborted_task = (struct iscsi_task *)sc->SCp.ptr;
	struct beiscsi_io_task *aborted_io_task;
	struct iscsi_conn *conn;
	struct beiscsi_conn *beiscsi_conn;
	struct beiscsi_hba *phba;
	struct iscsi_session *session;
	struct invalidate_command_table *inv_tbl;
	struct be_dma_mem nonemb_cmd;
	unsigned int cid, tag, num_invalidate;

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;

	spin_lock_bh(&session->lock);
	if (!aborted_task || !aborted_task->sc) {
		/* we raced */
		spin_unlock_bh(&session->lock);
		return SUCCESS;
	}

	aborted_io_task = aborted_task->dd_data;
	if (!aborted_io_task->scsi_cmnd) {
		/* raced or invalid command */
		spin_unlock_bh(&session->lock);
		return SUCCESS;
	}
	spin_unlock_bh(&session->lock);
	conn = aborted_task->conn;
	beiscsi_conn = conn->dd_data;
	phba = beiscsi_conn->phba;

	/* invalidate iocb */
	cid = beiscsi_conn->beiscsi_conn_cid;
	inv_tbl = phba->inv_tbl;
	memset(inv_tbl, 0x0, sizeof(*inv_tbl));
	inv_tbl->cid = cid;
	inv_tbl->icd = aborted_io_task->psgl_handle->sgl_index;
	num_invalidate = 1;
	nonemb_cmd.va = pci_alloc_consistent(phba->ctrl.pdev,
				sizeof(struct invalidate_commands_params_in),
				&nonemb_cmd.dma);
	if (nonemb_cmd.va == NULL) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_EH,
			    "BM_%d : Failed to allocate memory for"
			    "mgmt_invalidate_icds\n");
		return FAILED;
	}
	nonemb_cmd.size = sizeof(struct invalidate_commands_params_in);

	tag = mgmt_invalidate_icds(phba, inv_tbl, num_invalidate,
				   cid, &nonemb_cmd);
	if (!tag) {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_EH,
			    "BM_%d : mgmt_invalidate_icds could not be"
			    "submitted\n");
		pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);

		return FAILED;
	}

	beiscsi_mccq_compl(phba, tag, NULL, nonemb_cmd.va);
	pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
			    nonemb_cmd.va, nonemb_cmd.dma);
	return iscsi_eh_abort(sc);
}