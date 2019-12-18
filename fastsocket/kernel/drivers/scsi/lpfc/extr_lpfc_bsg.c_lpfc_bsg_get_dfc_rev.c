#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  a_Minor; int /*<<< orphan*/  a_Major; } ;
struct get_mgmt_rev_reply {TYPE_7__ info; } ;
struct get_mgmt_rev {int dummy; } ;
struct fc_bsg_request {int dummy; } ;
struct fc_bsg_job {int request_len; int reply_len; int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_8__* reply; TYPE_4__* request; TYPE_1__* shost; } ;
struct TYPE_13__ {scalar_t__ vendor_rsp; } ;
struct TYPE_14__ {TYPE_5__ vendor_reply; } ;
struct TYPE_16__ {int result; TYPE_6__ reply_data; } ;
struct TYPE_10__ {scalar_t__ vendor_cmd; } ;
struct TYPE_11__ {TYPE_2__ h_vendor; } ;
struct TYPE_12__ {TYPE_3__ rqst_data; } ;
struct TYPE_9__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int /*<<< orphan*/  MANAGEMENT_MAJOR_REV ; 
 int /*<<< orphan*/  MANAGEMENT_MINOR_REV ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 

__attribute__((used)) static int
lpfc_bsg_get_dfc_rev(struct fc_bsg_job *job)
{
	struct lpfc_vport *vport = (struct lpfc_vport *)job->shost->hostdata;
	struct lpfc_hba *phba = vport->phba;
	struct get_mgmt_rev *event_req;
	struct get_mgmt_rev_reply *event_reply;
	int rc = 0;

	if (job->request_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct get_mgmt_rev)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2740 Received GET_DFC_REV request below "
				"minimum size\n");
		rc = -EINVAL;
		goto job_error;
	}

	event_req = (struct get_mgmt_rev *)
		job->request->rqst_data.h_vendor.vendor_cmd;

	event_reply = (struct get_mgmt_rev_reply *)
		job->reply->reply_data.vendor_reply.vendor_rsp;

	if (job->reply_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct get_mgmt_rev_reply)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2741 Received GET_DFC_REV reply below "
				"minimum size\n");
		rc = -EINVAL;
		goto job_error;
	}

	event_reply->info.a_Major = MANAGEMENT_MAJOR_REV;
	event_reply->info.a_Minor = MANAGEMENT_MINOR_REV;
job_error:
	job->reply->result = rc;
	if (rc == 0)
		job->job_done(job);
	return rc;
}