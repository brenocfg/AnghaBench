#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ulp_bde64 {int dummy; } ;
struct send_mgmt_resp {int /*<<< orphan*/  tag; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; scalar_t__ virt; int /*<<< orphan*/  list; } ;
struct TYPE_12__ {scalar_t__ payload_len; } ;
struct fc_bsg_job {int /*<<< orphan*/ * dd_data; TYPE_5__* reply; TYPE_6__ request_payload; TYPE_4__* request; TYPE_1__* shost; } ;
struct TYPE_11__ {int result; scalar_t__ reply_payload_rcv_len; } ;
struct TYPE_8__ {scalar_t__ vendor_cmd; } ;
struct TYPE_9__ {TYPE_2__ h_vendor; } ;
struct TYPE_10__ {TYPE_3__ rqst_data; } ;
struct TYPE_7__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int BUF_SZ_4K ; 
 int EACCES ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IOCB_SUCCESS ; 
 int LPFC_BPL_SIZE ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct lpfc_dmabuf* lpfc_alloc_bsg_buffers (struct lpfc_hba*,scalar_t__,int,struct ulp_bde64*,int*) ; 
 int /*<<< orphan*/  lpfc_bsg_copy_data (struct lpfc_dmabuf*,TYPE_6__*,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_free_bsg_buffers (struct lpfc_hba*,struct lpfc_dmabuf*) ; 
 int lpfc_issue_ct_rsp (struct lpfc_hba*,struct fc_bsg_job*,int /*<<< orphan*/ ,struct lpfc_dmabuf*,struct lpfc_dmabuf*,int) ; 
 scalar_t__ lpfc_mbuf_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_bsg_send_mgmt_rsp(struct fc_bsg_job *job)
{
	struct lpfc_vport *vport = (struct lpfc_vport *)job->shost->hostdata;
	struct lpfc_hba *phba = vport->phba;
	struct send_mgmt_resp *mgmt_resp = (struct send_mgmt_resp *)
		job->request->rqst_data.h_vendor.vendor_cmd;
	struct ulp_bde64 *bpl;
	struct lpfc_dmabuf *bmp = NULL, *cmp = NULL;
	int bpl_entries;
	uint32_t tag = mgmt_resp->tag;
	unsigned long reqbfrcnt =
			(unsigned long)job->request_payload.payload_len;
	int rc = 0;

	/* in case no data is transferred */
	job->reply->reply_payload_rcv_len = 0;

	if (!reqbfrcnt || (reqbfrcnt > (80 * BUF_SZ_4K))) {
		rc = -ERANGE;
		goto send_mgmt_rsp_exit;
	}

	bmp = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (!bmp) {
		rc = -ENOMEM;
		goto send_mgmt_rsp_exit;
	}

	bmp->virt = lpfc_mbuf_alloc(phba, 0, &bmp->phys);
	if (!bmp->virt) {
		rc = -ENOMEM;
		goto send_mgmt_rsp_free_bmp;
	}

	INIT_LIST_HEAD(&bmp->list);
	bpl = (struct ulp_bde64 *) bmp->virt;
	bpl_entries = (LPFC_BPL_SIZE/sizeof(struct ulp_bde64));
	cmp = lpfc_alloc_bsg_buffers(phba, job->request_payload.payload_len,
				     1, bpl, &bpl_entries);
	if (!cmp) {
		rc = -ENOMEM;
		goto send_mgmt_rsp_free_bmp;
	}
	lpfc_bsg_copy_data(cmp, &job->request_payload,
			   job->request_payload.payload_len, 1);

	rc = lpfc_issue_ct_rsp(phba, job, tag, cmp, bmp, bpl_entries);

	if (rc == IOCB_SUCCESS)
		return 0; /* done for now */

	rc = -EACCES;

	lpfc_free_bsg_buffers(phba, cmp);

send_mgmt_rsp_free_bmp:
	if (bmp->virt)
		lpfc_mbuf_free(phba, bmp->virt, bmp->phys);
	kfree(bmp);
send_mgmt_rsp_exit:
	/* make error code available to userspace */
	job->reply->result = rc;
	job->dd_data = NULL;
	return rc;
}