#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct sgl_handle {scalar_t__ sgl_index; } ;
struct iscsi_task {int hdr_max; scalar_t__ sc; struct iscsi_hdr* hdr; scalar_t__ itt; struct iscsi_conn* conn; struct beiscsi_io_task* dd_data; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {struct beiscsi_conn* dd_data; } ;
struct hwi_wrb_context {int dummy; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct beiscsi_session {int /*<<< orphan*/  bhs_pool; } ;
struct TYPE_8__ {int /*<<< orphan*/  address; } ;
struct TYPE_9__ {TYPE_1__ a64; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct beiscsi_io_task {TYPE_5__* cmd_bhs; TYPE_3__ bhs_pa; TYPE_7__* pwrb_handle; struct sgl_handle* psgl_handle; int /*<<< orphan*/ * scsi_cmnd; struct beiscsi_conn* conn; void* libiscsi_itt; } ;
struct beiscsi_hba {struct hwi_controller* phwi_ctrlr; int /*<<< orphan*/  mgmt_sgl_lock; int /*<<< orphan*/  io_sgl_lock; } ;
struct beiscsi_conn {int login_in_progress; int /*<<< orphan*/  beiscsi_conn_cid; TYPE_7__* plogin_wrb_handle; struct sgl_handle* plogin_sgl_handle; struct iscsi_task* task; struct beiscsi_session* beiscsi_sess; struct beiscsi_hba* phba; } ;
struct be_cmd_bhs {int dummy; } ;
typedef  void* itt_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_13__ {struct iscsi_task* pio_handle; scalar_t__ wrb_index; } ;
struct TYPE_11__ {void* itt; } ;
struct TYPE_12__ {TYPE_4__ iscsi_hdr; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_IO ; 
 size_t BE_GET_CRI_FROM_CID (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ISCSI_OPCODE_MASK ; 
 int ISCSI_OP_LOGIN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 struct sgl_handle* alloc_io_sgl_handle (struct beiscsi_hba*) ; 
 struct sgl_handle* alloc_mgmt_sgl_handle (struct beiscsi_hba*) ; 
 void* alloc_wrb_handle (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  free_io_sgl_handle (struct beiscsi_hba*,struct sgl_handle*) ; 
 int /*<<< orphan*/  free_mgmt_sgl_handle (struct beiscsi_hba*,struct sgl_handle*) ; 
 int /*<<< orphan*/  free_wrb_handle (struct beiscsi_hba*,struct hwi_wrb_context*,TYPE_7__*) ; 
 TYPE_5__* pci_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int beiscsi_alloc_pdu(struct iscsi_task *task, uint8_t opcode)
{
	struct beiscsi_io_task *io_task = task->dd_data;
	struct iscsi_conn *conn = task->conn;
	struct beiscsi_conn *beiscsi_conn = conn->dd_data;
	struct beiscsi_hba *phba = beiscsi_conn->phba;
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	itt_t itt;
	uint16_t cri_index = 0;
	struct beiscsi_session *beiscsi_sess = beiscsi_conn->beiscsi_sess;
	dma_addr_t paddr;

	io_task->cmd_bhs = pci_pool_alloc(beiscsi_sess->bhs_pool,
					  GFP_ATOMIC, &paddr);
	if (!io_task->cmd_bhs)
		return -ENOMEM;
	io_task->bhs_pa.u.a64.address = paddr;
	io_task->libiscsi_itt = (itt_t)task->itt;
	io_task->conn = beiscsi_conn;

	task->hdr = (struct iscsi_hdr *)&io_task->cmd_bhs->iscsi_hdr;
	task->hdr_max = sizeof(struct be_cmd_bhs);
	io_task->psgl_handle = NULL;
	io_task->pwrb_handle = NULL;

	if (task->sc) {
		spin_lock(&phba->io_sgl_lock);
		io_task->psgl_handle = alloc_io_sgl_handle(phba);
		spin_unlock(&phba->io_sgl_lock);
		if (!io_task->psgl_handle) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_IO | BEISCSI_LOG_CONFIG,
				    "BM_%d : Alloc of IO_SGL_ICD Failed"
				    "for the CID : %d\n",
				    beiscsi_conn->beiscsi_conn_cid);
			goto free_hndls;
		}
		io_task->pwrb_handle = alloc_wrb_handle(phba,
					beiscsi_conn->beiscsi_conn_cid);
		if (!io_task->pwrb_handle) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_IO | BEISCSI_LOG_CONFIG,
				    "BM_%d : Alloc of WRB_HANDLE Failed"
				    "for the CID : %d\n",
				    beiscsi_conn->beiscsi_conn_cid);
			goto free_io_hndls;
		}
	} else {
		io_task->scsi_cmnd = NULL;
		if ((opcode & ISCSI_OPCODE_MASK) == ISCSI_OP_LOGIN) {
			beiscsi_conn->task = task;
			if (!beiscsi_conn->login_in_progress) {
				spin_lock(&phba->mgmt_sgl_lock);
				io_task->psgl_handle = (struct sgl_handle *)
						alloc_mgmt_sgl_handle(phba);
				spin_unlock(&phba->mgmt_sgl_lock);
				if (!io_task->psgl_handle) {
					beiscsi_log(phba, KERN_ERR,
						    BEISCSI_LOG_IO |
						    BEISCSI_LOG_CONFIG,
						    "BM_%d : Alloc of MGMT_SGL_ICD Failed"
						    "for the CID : %d\n",
						    beiscsi_conn->
						    beiscsi_conn_cid);
					goto free_hndls;
				}

				beiscsi_conn->login_in_progress = 1;
				beiscsi_conn->plogin_sgl_handle =
							io_task->psgl_handle;
				io_task->pwrb_handle =
					alloc_wrb_handle(phba,
					beiscsi_conn->beiscsi_conn_cid);
				if (!io_task->pwrb_handle) {
					beiscsi_log(phba, KERN_ERR,
						    BEISCSI_LOG_IO |
						    BEISCSI_LOG_CONFIG,
						    "BM_%d : Alloc of WRB_HANDLE Failed"
						    "for the CID : %d\n",
						    beiscsi_conn->
						    beiscsi_conn_cid);
					goto free_mgmt_hndls;
				}
				beiscsi_conn->plogin_wrb_handle =
							io_task->pwrb_handle;

			} else {
				io_task->psgl_handle =
						beiscsi_conn->plogin_sgl_handle;
				io_task->pwrb_handle =
						beiscsi_conn->plogin_wrb_handle;
			}
		} else {
			spin_lock(&phba->mgmt_sgl_lock);
			io_task->psgl_handle = alloc_mgmt_sgl_handle(phba);
			spin_unlock(&phba->mgmt_sgl_lock);
			if (!io_task->psgl_handle) {
				beiscsi_log(phba, KERN_ERR,
					    BEISCSI_LOG_IO |
					    BEISCSI_LOG_CONFIG,
					    "BM_%d : Alloc of MGMT_SGL_ICD Failed"
					    "for the CID : %d\n",
					    beiscsi_conn->
					    beiscsi_conn_cid);
				goto free_hndls;
			}
			io_task->pwrb_handle =
					alloc_wrb_handle(phba,
					beiscsi_conn->beiscsi_conn_cid);
			if (!io_task->pwrb_handle) {
				beiscsi_log(phba, KERN_ERR,
					    BEISCSI_LOG_IO | BEISCSI_LOG_CONFIG,
					    "BM_%d : Alloc of WRB_HANDLE Failed"
					    "for the CID : %d\n",
					    beiscsi_conn->beiscsi_conn_cid);
				goto free_mgmt_hndls;
			}

		}
	}
	itt = (itt_t) cpu_to_be32(((unsigned int)io_task->pwrb_handle->
				 wrb_index << 16) | (unsigned int)
				(io_task->psgl_handle->sgl_index));
	io_task->pwrb_handle->pio_handle = task;

	io_task->cmd_bhs->iscsi_hdr.itt = itt;
	return 0;

free_io_hndls:
	spin_lock(&phba->io_sgl_lock);
	free_io_sgl_handle(phba, io_task->psgl_handle);
	spin_unlock(&phba->io_sgl_lock);
	goto free_hndls;
free_mgmt_hndls:
	spin_lock(&phba->mgmt_sgl_lock);
	free_mgmt_sgl_handle(phba, io_task->psgl_handle);
	io_task->psgl_handle = NULL;
	spin_unlock(&phba->mgmt_sgl_lock);
free_hndls:
	phwi_ctrlr = phba->phwi_ctrlr;
	cri_index = BE_GET_CRI_FROM_CID(
	beiscsi_conn->beiscsi_conn_cid);
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];
	if (io_task->pwrb_handle)
		free_wrb_handle(phba, pwrb_context, io_task->pwrb_handle);
	io_task->pwrb_handle = NULL;
	pci_pool_free(beiscsi_sess->bhs_pool, io_task->cmd_bhs,
		      io_task->bhs_pa.u.a64.address);
	io_task->cmd_bhs = NULL;
	return -ENOMEM;
}