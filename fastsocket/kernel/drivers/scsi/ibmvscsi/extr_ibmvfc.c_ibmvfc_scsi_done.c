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
typedef  scalar_t__ u32 ;
struct scsi_cmnd {int result; scalar_t__ underflow; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  device; int /*<<< orphan*/  sense_buffer; } ;
struct TYPE_4__ {scalar_t__ sense; } ;
struct ibmvfc_fcp_rsp {scalar_t__ fcp_sense_len; int flags; scalar_t__ fcp_rsp_len; TYPE_2__ data; int /*<<< orphan*/  fcp_resid; } ;
struct ibmvfc_event {scalar_t__ eh_comp; struct scsi_cmnd* cmnd; TYPE_1__* xfer_iu; } ;
struct ibmvfc_cmd {int response_flags; int status; scalar_t__ error; int /*<<< orphan*/  adapter_resid; struct ibmvfc_fcp_rsp rsp; } ;
struct TYPE_3__ {struct ibmvfc_cmd cmd; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int FCP_RESID_OVER ; 
 int FCP_RESID_UNDER ; 
 int FCP_RSP_LEN_VALID ; 
 int FCP_SNS_LEN_VALID ; 
 int IBMVFC_ADAPTER_RESID_VALID ; 
 scalar_t__ IBMVFC_PLOGI_REQUIRED ; 
 int IBMVFC_VIOS_FAILURE ; 
 scalar_t__ SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int ibmvfc_get_err_result (struct ibmvfc_cmd*) ; 
 int /*<<< orphan*/  ibmvfc_log_error (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_relogin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 scalar_t__ scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void ibmvfc_scsi_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_cmd *vfc_cmd = &evt->xfer_iu->cmd;
	struct ibmvfc_fcp_rsp *rsp = &vfc_cmd->rsp;
	struct scsi_cmnd *cmnd = evt->cmnd;
	u32 rsp_len = 0;
	u32 sense_len = rsp->fcp_sense_len;

	if (cmnd) {
		if (vfc_cmd->response_flags & IBMVFC_ADAPTER_RESID_VALID)
			scsi_set_resid(cmnd, vfc_cmd->adapter_resid);
		else if (rsp->flags & FCP_RESID_UNDER)
			scsi_set_resid(cmnd, rsp->fcp_resid);
		else
			scsi_set_resid(cmnd, 0);

		if (vfc_cmd->status) {
			cmnd->result = ibmvfc_get_err_result(vfc_cmd);

			if (rsp->flags & FCP_RSP_LEN_VALID)
				rsp_len = rsp->fcp_rsp_len;
			if ((sense_len + rsp_len) > SCSI_SENSE_BUFFERSIZE)
				sense_len = SCSI_SENSE_BUFFERSIZE - rsp_len;
			if ((rsp->flags & FCP_SNS_LEN_VALID) && rsp->fcp_sense_len && rsp_len <= 8)
				memcpy(cmnd->sense_buffer, rsp->data.sense + rsp_len, sense_len);
			if ((vfc_cmd->status & IBMVFC_VIOS_FAILURE) && (vfc_cmd->error == IBMVFC_PLOGI_REQUIRED))
				ibmvfc_relogin(cmnd->device);

			if (!cmnd->result && (!scsi_get_resid(cmnd) || (rsp->flags & FCP_RESID_OVER)))
				cmnd->result = (DID_ERROR << 16);

			ibmvfc_log_error(evt);
		}

		if (!cmnd->result &&
		    (scsi_bufflen(cmnd) - scsi_get_resid(cmnd) < cmnd->underflow))
			cmnd->result = (DID_ERROR << 16);

		scsi_dma_unmap(cmnd);
		cmnd->scsi_done(cmnd);
	}

	if (evt->eh_comp)
		complete(evt->eh_comp);

	ibmvfc_free_event(evt);
}