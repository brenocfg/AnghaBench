#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ sts_cont_entry_t ;
struct scsi_qla_host {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  result; } ;
struct rsp_que {TYPE_2__* status_srb; struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* done ) (struct qla_hw_data*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ srb_t ;

/* Variables and functions */
 int GET_CMD_SENSE_LEN (TYPE_2__*) ; 
 int* GET_CMD_SENSE_PTR (TYPE_2__*) ; 
 struct scsi_cmnd* GET_CMD_SP (TYPE_2__*) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  SET_CMD_SENSE_LEN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SET_CMD_SENSE_PTR (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  host_to_fcp_swap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct scsi_qla_host* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_io ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,struct scsi_qla_host*,int,int*,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla2x00_status_cont_entry(struct rsp_que *rsp, sts_cont_entry_t *pkt)
{
	uint8_t	sense_sz = 0;
	struct qla_hw_data *ha = rsp->hw;
	struct scsi_qla_host *vha = pci_get_drvdata(ha->pdev);
	srb_t *sp = rsp->status_srb;
	struct scsi_cmnd *cp;
	uint32_t sense_len;
	uint8_t *sense_ptr;

	if (!sp || !GET_CMD_SENSE_LEN(sp))
		return;

	sense_len = GET_CMD_SENSE_LEN(sp);
	sense_ptr = GET_CMD_SENSE_PTR(sp);

	cp = GET_CMD_SP(sp);
	if (cp == NULL) {
		ql_log(ql_log_warn, vha, 0x3025,
		    "cmd is NULL: already returned to OS (sp=%p).\n", sp);

		rsp->status_srb = NULL;
		return;
	}

	if (sense_len > sizeof(pkt->data))
		sense_sz = sizeof(pkt->data);
	else
		sense_sz = sense_len;

	/* Move sense data. */
	if (IS_FWI2_CAPABLE(ha))
		host_to_fcp_swap(pkt->data, sizeof(pkt->data));
	memcpy(sense_ptr, pkt->data, sense_sz);
	ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x302c,
		sense_ptr, sense_sz);

	sense_len -= sense_sz;
	sense_ptr += sense_sz;

	SET_CMD_SENSE_PTR(sp, sense_ptr);
	SET_CMD_SENSE_LEN(sp, sense_len);

	/* Place command on done queue. */
	if (sense_len == 0) {
		rsp->status_srb = NULL;
		sp->done(ha, sp, cp->result);
	}
}