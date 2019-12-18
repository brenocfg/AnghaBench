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
struct i_t_dpdu_cqe {int dummy; } ;
struct hwi_controller {int dummy; } ;
struct hwi_async_pdu_context {int dummy; } ;
struct beiscsi_hba {struct hwi_controller* phwi_ctrlr; } ;
struct beiscsi_conn {int dummy; } ;
struct async_pdu_handle {scalar_t__ is_header; scalar_t__ consumed; int /*<<< orphan*/  cri; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct hwi_async_pdu_context* HWI_GET_ASYNC_PDU_CTX (struct hwi_controller*) ; 
 int /*<<< orphan*/  hwi_free_async_msg (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 struct async_pdu_handle* hwi_get_async_handle (struct beiscsi_hba*,struct beiscsi_conn*,struct hwi_async_pdu_context*,struct i_t_dpdu_cqe*,unsigned int*) ; 
 int /*<<< orphan*/  hwi_post_async_buffers (struct beiscsi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  hwi_update_async_writables (struct beiscsi_hba*,struct hwi_async_pdu_context*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void hwi_flush_default_pdu_buffer(struct beiscsi_hba *phba,
					 struct beiscsi_conn *beiscsi_conn,
					 struct i_t_dpdu_cqe *pdpdu_cqe)
{
	struct hwi_controller *phwi_ctrlr;
	struct hwi_async_pdu_context *pasync_ctx;
	struct async_pdu_handle *pasync_handle = NULL;
	unsigned int cq_index = -1;

	phwi_ctrlr = phba->phwi_ctrlr;
	pasync_ctx = HWI_GET_ASYNC_PDU_CTX(phwi_ctrlr);

	pasync_handle = hwi_get_async_handle(phba, beiscsi_conn, pasync_ctx,
					     pdpdu_cqe, &cq_index);
	BUG_ON(pasync_handle->is_header != 0);
	if (pasync_handle->consumed == 0)
		hwi_update_async_writables(phba, pasync_ctx,
					   pasync_handle->is_header, cq_index);

	hwi_free_async_msg(phba, pasync_handle->cri);
	hwi_post_async_buffers(phba, pasync_handle->is_header);
}