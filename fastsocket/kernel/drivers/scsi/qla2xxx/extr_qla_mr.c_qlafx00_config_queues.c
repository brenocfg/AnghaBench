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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct rsp_que {scalar_t__ length; void* dma; void* ring; } ;
struct req_que {scalar_t__ length; void* dma; void* ring; } ;
struct qla_hw_data {scalar_t__ req_que_len; int req_que_off; scalar_t__ rsp_que_len; int rsp_que_off; int /*<<< orphan*/  pdev; scalar_t__ iobase; struct rsp_que** rsp_q_map; struct rsp_que** req_q_map; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 void* pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,struct rsp_que*,void*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_pci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
qlafx00_config_queues(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];
	struct rsp_que *rsp = ha->rsp_q_map[0];
	dma_addr_t bar2_hdl = pci_resource_start(ha->pdev, 2);

	req->length = ha->req_que_len;
	req->ring = (void *)ha->iobase + ha->req_que_off;
	req->dma = bar2_hdl + ha->req_que_off;
	if ((!req->ring) || (req->length == 0)) {
		ql_log_pci(ql_log_info, ha->pdev, 0x012f,
		    "Unable to allocate memory for req_ring\n");
		return QLA_FUNCTION_FAILED;
	}

	ql_dbg(ql_dbg_init, vha, 0x0130,
	    "req: %p req_ring pointer %p req len 0x%x "
	    "req off 0x%x\n, req->dma: 0x%llx",
	    req, req->ring, req->length,
	    ha->req_que_off, (u64)req->dma);

	rsp->length = ha->rsp_que_len;
	rsp->ring = (void *)ha->iobase + ha->rsp_que_off;
	rsp->dma = bar2_hdl + ha->rsp_que_off;
	if ((!rsp->ring) || (rsp->length == 0)) {
		ql_log_pci(ql_log_info, ha->pdev, 0x0131,
		    "Unable to allocate memory for rsp_ring\n");
		return QLA_FUNCTION_FAILED;
	}

	ql_dbg(ql_dbg_init, vha, 0x0132,
	    "rsp: %p rsp_ring pointer %p rsp len 0x%x "
	    "rsp off 0x%x, rsp->dma: 0x%llx\n",
	    rsp, rsp->ring, rsp->length,
	    ha->rsp_que_off, (u64)rsp->dma);

	return QLA_SUCCESS;
}