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
 int BFA_STATUS_OK ; 
 int EINVAL ; 
#define  FC_BSG_HST_CT 132 
#define  FC_BSG_HST_ELS_NOLOGIN 131 
#define  FC_BSG_HST_VENDOR 130 
#define  FC_BSG_RPT_CT 129 
#define  FC_BSG_RPT_ELS 128 
 int bfad_im_bsg_els_ct_request (struct fc_bsg_job*) ; 
 int bfad_im_bsg_vendor_request (struct fc_bsg_job*) ; 

int
bfad_im_bsg_request(struct fc_bsg_job *job)
{
	uint32_t rc = BFA_STATUS_OK;

	switch (job->request->msgcode) {
	case FC_BSG_HST_VENDOR:
		/* Process BSG HST Vendor requests */
		rc = bfad_im_bsg_vendor_request(job);
		break;
	case FC_BSG_HST_ELS_NOLOGIN:
	case FC_BSG_RPT_ELS:
	case FC_BSG_HST_CT:
	case FC_BSG_RPT_CT:
		/* Process BSG ELS/CT commands */
		rc = bfad_im_bsg_els_ct_request(job);
		break;
	default:
		job->reply->result = rc = -EINVAL;
		job->reply->reply_payload_rcv_len = 0;
		break;
	}

	return rc;
}