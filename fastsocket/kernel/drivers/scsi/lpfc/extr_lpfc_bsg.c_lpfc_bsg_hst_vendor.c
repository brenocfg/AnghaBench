#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fc_bsg_job {TYPE_1__* reply; TYPE_3__* request; } ;
struct TYPE_6__ {int* vendor_cmd; } ;
struct TYPE_8__ {TYPE_2__ h_vendor; } ;
struct TYPE_7__ {TYPE_4__ rqst_data; } ;
struct TYPE_5__ {int result; int /*<<< orphan*/  reply_payload_rcv_len; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LPFC_BSG_VENDOR_DIAG_MODE 138 
#define  LPFC_BSG_VENDOR_DIAG_MODE_END 137 
#define  LPFC_BSG_VENDOR_DIAG_RUN_LOOPBACK 136 
#define  LPFC_BSG_VENDOR_GET_CT_EVENT 135 
#define  LPFC_BSG_VENDOR_GET_MGMT_REV 134 
#define  LPFC_BSG_VENDOR_LINK_DIAG_TEST 133 
#define  LPFC_BSG_VENDOR_MBOX 132 
#define  LPFC_BSG_VENDOR_MENLO_CMD 131 
#define  LPFC_BSG_VENDOR_MENLO_DATA 130 
#define  LPFC_BSG_VENDOR_SEND_MGMT_RESP 129 
#define  LPFC_BSG_VENDOR_SET_CT_EVENT 128 
 int lpfc_bsg_diag_loopback_mode (struct fc_bsg_job*) ; 
 int lpfc_bsg_diag_loopback_run (struct fc_bsg_job*) ; 
 int lpfc_bsg_get_dfc_rev (struct fc_bsg_job*) ; 
 int lpfc_bsg_hba_get_event (struct fc_bsg_job*) ; 
 int lpfc_bsg_hba_set_event (struct fc_bsg_job*) ; 
 int lpfc_bsg_mbox_cmd (struct fc_bsg_job*) ; 
 int lpfc_bsg_send_mgmt_rsp (struct fc_bsg_job*) ; 
 int lpfc_menlo_cmd (struct fc_bsg_job*) ; 
 int lpfc_sli4_bsg_diag_mode_end (struct fc_bsg_job*) ; 
 int lpfc_sli4_bsg_link_diag_test (struct fc_bsg_job*) ; 

__attribute__((used)) static int
lpfc_bsg_hst_vendor(struct fc_bsg_job *job)
{
	int command = job->request->rqst_data.h_vendor.vendor_cmd[0];
	int rc;

	switch (command) {
	case LPFC_BSG_VENDOR_SET_CT_EVENT:
		rc = lpfc_bsg_hba_set_event(job);
		break;
	case LPFC_BSG_VENDOR_GET_CT_EVENT:
		rc = lpfc_bsg_hba_get_event(job);
		break;
	case LPFC_BSG_VENDOR_SEND_MGMT_RESP:
		rc = lpfc_bsg_send_mgmt_rsp(job);
		break;
	case LPFC_BSG_VENDOR_DIAG_MODE:
		rc = lpfc_bsg_diag_loopback_mode(job);
		break;
	case LPFC_BSG_VENDOR_DIAG_MODE_END:
		rc = lpfc_sli4_bsg_diag_mode_end(job);
		break;
	case LPFC_BSG_VENDOR_DIAG_RUN_LOOPBACK:
		rc = lpfc_bsg_diag_loopback_run(job);
		break;
	case LPFC_BSG_VENDOR_LINK_DIAG_TEST:
		rc = lpfc_sli4_bsg_link_diag_test(job);
		break;
	case LPFC_BSG_VENDOR_GET_MGMT_REV:
		rc = lpfc_bsg_get_dfc_rev(job);
		break;
	case LPFC_BSG_VENDOR_MBOX:
		rc = lpfc_bsg_mbox_cmd(job);
		break;
	case LPFC_BSG_VENDOR_MENLO_CMD:
	case LPFC_BSG_VENDOR_MENLO_DATA:
		rc = lpfc_menlo_cmd(job);
		break;
	default:
		rc = -EINVAL;
		job->reply->reply_payload_rcv_len = 0;
		/* make error code available to userspace */
		job->reply->result = rc;
		break;
	}

	return rc;
}