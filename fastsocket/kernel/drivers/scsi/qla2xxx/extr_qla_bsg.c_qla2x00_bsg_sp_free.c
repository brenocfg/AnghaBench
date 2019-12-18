#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_mt_iocb_rqst_fx00 {int flags; } ;
struct qla_hw_data {TYPE_6__* pdev; } ;
struct TYPE_18__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct TYPE_16__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {TYPE_7__ reply_payload; TYPE_5__ request_payload; TYPE_4__* request; } ;
struct TYPE_12__ {struct fc_bsg_job* bsg_job; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_10__* fcport; TYPE_1__ u; } ;
typedef  TYPE_8__ srb_t ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int /*<<< orphan*/ * vendor_cmd; } ;
struct TYPE_14__ {TYPE_2__ h_vendor; } ;
struct TYPE_15__ {TYPE_3__ rqst_data; } ;
struct TYPE_11__ {struct scsi_qla_host* vha; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ SRB_CT_CMD ; 
 scalar_t__ SRB_ELS_CMD_HST ; 
 int SRB_FXDISC_REQ_DMA_VALID ; 
 int SRB_FXDISC_RESP_DMA_VALID ; 
 scalar_t__ SRB_FXIOCB_BCMD ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_10__*) ; 
 int /*<<< orphan*/  qla2x00_rel_sp (struct scsi_qla_host*,TYPE_8__*) ; 

void
qla2x00_bsg_sp_free(void *data, void *ptr)
{
	srb_t *sp = (srb_t *)ptr;
	struct scsi_qla_host *vha = sp->fcport->vha;
	struct fc_bsg_job *bsg_job = sp->u.bsg_job;
	struct qla_hw_data *ha = vha->hw;
	struct qla_mt_iocb_rqst_fx00 *piocb_rqst;

	if (sp->type == SRB_FXIOCB_BCMD) {
		piocb_rqst = (struct qla_mt_iocb_rqst_fx00 *)
		    &bsg_job->request->rqst_data.h_vendor.vendor_cmd[1];

		if (piocb_rqst->flags & SRB_FXDISC_REQ_DMA_VALID)
			dma_unmap_sg(&ha->pdev->dev,
			    bsg_job->request_payload.sg_list,
			    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

		if (piocb_rqst->flags & SRB_FXDISC_RESP_DMA_VALID)
			dma_unmap_sg(&ha->pdev->dev,
			    bsg_job->reply_payload.sg_list,
			    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	} else {
		dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

		dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	}

	if (sp->type == SRB_CT_CMD ||
	    sp->type == SRB_FXIOCB_BCMD ||
	    sp->type == SRB_ELS_CMD_HST)
		kfree(sp->fcport);
	qla2x00_rel_sp(vha, sp);
}