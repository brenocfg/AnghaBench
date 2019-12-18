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
struct rsp_que {int dummy; } ;
struct req_que {int dummy; } ;
struct qla_hw_data {int max_req_queues; int max_rsp_queues; struct req_que** req_q_map; int /*<<< orphan*/  req_qid_map; int /*<<< orphan*/  rsp_qid_map; struct rsp_que** rsp_q_map; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct req_que**) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla2x00_alloc_queues(struct qla_hw_data *ha, struct req_que *req,
				struct rsp_que *rsp)
{
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	ha->req_q_map = kzalloc(sizeof(struct req_que *) * ha->max_req_queues,
				GFP_KERNEL);
	if (!ha->req_q_map) {
		ql_log(ql_log_fatal, vha, 0x003b,
		    "Unable to allocate memory for request queue ptrs.\n");
		goto fail_req_map;
	}

	ha->rsp_q_map = kzalloc(sizeof(struct rsp_que *) * ha->max_rsp_queues,
				GFP_KERNEL);
	if (!ha->rsp_q_map) {
		ql_log(ql_log_fatal, vha, 0x003c,
		    "Unable to allocate memory for response queue ptrs.\n");
		goto fail_rsp_map;
	}
	/*
	 * Make sure we record at least the request and response queue zero in
	 * case we need to free them if part of the probe fails.
	 */
	ha->rsp_q_map[0] = rsp;
	ha->req_q_map[0] = req;
	set_bit(0, ha->rsp_qid_map);
	set_bit(0, ha->req_qid_map);
	return 1;

fail_rsp_map:
	kfree(ha->req_q_map);
	ha->req_q_map = NULL;
fail_req_map:
	return -ENOMEM;
}