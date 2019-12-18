#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_req {int status; TYPE_3__* qtcb; } ;
struct fcp_resp_with_ext {int dummy; } ;
struct fcp_resp_rsp_info {scalar_t__ rsp_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcp_rsp; } ;
struct TYPE_5__ {TYPE_1__ io; } ;
struct TYPE_6__ {TYPE_2__ bottom; } ;

/* Variables and functions */
 scalar_t__ FCP_TMF_CMPL ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int ZFCP_STATUS_FSFREQ_TMFUNCFAILED ; 

__attribute__((used)) static void zfcp_fsf_send_fcp_ctm_handler(struct zfcp_fsf_req *req)
{
	struct fcp_resp_with_ext *fcp_rsp;
	struct fcp_resp_rsp_info *rsp_info;

	fcp_rsp = (struct fcp_resp_with_ext *) &req->qtcb->bottom.io.fcp_rsp;
	rsp_info = (struct fcp_resp_rsp_info *) &fcp_rsp[1];

	if ((rsp_info->rsp_code != FCP_TMF_CMPL) ||
	     (req->status & ZFCP_STATUS_FSFREQ_ERROR))
		req->status |= ZFCP_STATUS_FSFREQ_TMFUNCFAILED;
}