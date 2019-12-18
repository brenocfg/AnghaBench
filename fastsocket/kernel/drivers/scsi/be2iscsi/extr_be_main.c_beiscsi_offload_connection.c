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
typedef  int u32 ;
struct wrb_handle {int wrb_index; int /*<<< orphan*/  pwrb; } ;
struct iscsi_task {TYPE_1__* conn; } ;
struct iscsi_target_context_update_wrb {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct beiscsi_offload_params {int dummy; } ;
struct beiscsi_hba {scalar_t__ db_va; int /*<<< orphan*/  init_mem; } ;
struct beiscsi_conn {int beiscsi_conn_cid; scalar_t__ login_in_progress; struct iscsi_task* task; struct beiscsi_hba* phba; } ;
struct TYPE_2__ {struct iscsi_session* session; } ;

/* Variables and functions */
 int DB_DEF_PDU_NUM_POSTED_SHIFT ; 
 int DB_DEF_PDU_WRB_INDEX_MASK ; 
 int DB_DEF_PDU_WRB_INDEX_SHIFT ; 
 scalar_t__ DB_TXULP0_OFFSET ; 
 int DB_WRB_POST_CID_MASK ; 
 struct wrb_handle* alloc_wrb_handle (struct beiscsi_hba*,int) ; 
 int /*<<< orphan*/  be_dws_le_to_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  beiscsi_cleanup_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  beiscsi_offload_cxn_v0 (struct beiscsi_offload_params*,struct wrb_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_offload_cxn_v2 (struct beiscsi_offload_params*,struct wrb_handle*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 scalar_t__ is_chip_be2_be3r (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
beiscsi_offload_connection(struct beiscsi_conn *beiscsi_conn,
			   struct beiscsi_offload_params *params)
{
	struct wrb_handle *pwrb_handle;
	struct beiscsi_hba *phba = beiscsi_conn->phba;
	struct iscsi_task *task = beiscsi_conn->task;
	struct iscsi_session *session = task->conn->session;
	u32 doorbell = 0;

	/*
	 * We can always use 0 here because it is reserved by libiscsi for
	 * login/startup related tasks.
	 */
	beiscsi_conn->login_in_progress = 0;
	spin_lock_bh(&session->lock);
	beiscsi_cleanup_task(task);
	spin_unlock_bh(&session->lock);

	pwrb_handle = alloc_wrb_handle(phba, beiscsi_conn->beiscsi_conn_cid);

	/* Check for the adapter family */
	if (is_chip_be2_be3r(phba))
		beiscsi_offload_cxn_v0(params, pwrb_handle,
				       phba->init_mem);
	else
		beiscsi_offload_cxn_v2(params, pwrb_handle);

	be_dws_le_to_cpu(pwrb_handle->pwrb,
			 sizeof(struct iscsi_target_context_update_wrb));

	doorbell |= beiscsi_conn->beiscsi_conn_cid & DB_WRB_POST_CID_MASK;
	doorbell |= (pwrb_handle->wrb_index & DB_DEF_PDU_WRB_INDEX_MASK)
			     << DB_DEF_PDU_WRB_INDEX_SHIFT;
	doorbell |= 1 << DB_DEF_PDU_NUM_POSTED_SHIFT;

	iowrite32(doorbell, phba->db_va + DB_TXULP0_OFFSET);
}