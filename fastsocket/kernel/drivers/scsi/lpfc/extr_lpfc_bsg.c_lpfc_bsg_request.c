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
typedef  int uint32_t ;
struct fc_bsg_job {TYPE_2__* reply; TYPE_1__* request; } ;
struct TYPE_4__ {int result; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct TYPE_3__ {int msgcode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FC_BSG_HST_VENDOR 130 
#define  FC_BSG_RPT_CT 129 
#define  FC_BSG_RPT_ELS 128 
 int lpfc_bsg_hst_vendor (struct fc_bsg_job*) ; 
 int lpfc_bsg_rport_els (struct fc_bsg_job*) ; 
 int lpfc_bsg_send_mgmt_cmd (struct fc_bsg_job*) ; 

int
lpfc_bsg_request(struct fc_bsg_job *job)
{
	uint32_t msgcode;
	int rc;

	msgcode = job->request->msgcode;
	switch (msgcode) {
	case FC_BSG_HST_VENDOR:
		rc = lpfc_bsg_hst_vendor(job);
		break;
	case FC_BSG_RPT_ELS:
		rc = lpfc_bsg_rport_els(job);
		break;
	case FC_BSG_RPT_CT:
		rc = lpfc_bsg_send_mgmt_cmd(job);
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