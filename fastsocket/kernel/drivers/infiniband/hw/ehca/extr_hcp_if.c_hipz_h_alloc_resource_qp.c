#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u64 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_14__ {unsigned long handle; } ;
struct TYPE_13__ {int page_size; int max_wr; int max_sge; void* queue_size; void* act_nr_sges; void* act_nr_wqes; } ;
struct TYPE_12__ {int page_size; int max_wr; int max_sge; void* queue_size; void* act_nr_sges; void* act_nr_wqes; } ;
struct TYPE_11__ {int value; } ;
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct ehca_alloc_qp_parms {int ext_type; int servicetype; int sigtype; int qp_storage; int ll_comp_flags; int ud_av_l_key_ctl; int srq_token; int srq_limit; int srq_qpn; TYPE_7__ qp_handle; int /*<<< orphan*/  galpas; TYPE_6__ rqueue; TYPE_5__ squeue; void* real_qp_num; TYPE_4__ pd; scalar_t__ token; TYPE_3__ eq_handle; TYPE_2__ recv_cq_handle; TYPE_1__ send_cq_handle; } ;

/* Variables and functions */
 scalar_t__ EHCA_BMASK_GET (int /*<<< orphan*/ ,unsigned long) ; 
 int EHCA_BMASK_SET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ EQPT_SRQ ; 
 int /*<<< orphan*/  H_ALLOC_RESOURCE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_ACT_OUTST_RECV_WR ; 
 int /*<<< orphan*/  H_ALL_RES_QP_ACT_OUTST_SEND_WR ; 
 int /*<<< orphan*/  H_ALL_RES_QP_ACT_RECV_SGE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_ACT_SEND_SGE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_ENHANCED_OPS ; 
 int /*<<< orphan*/  H_ALL_RES_QP_LL_RQ_CQE_POSTING ; 
 int /*<<< orphan*/  H_ALL_RES_QP_LL_SQ_CQE_POSTING ; 
 int /*<<< orphan*/  H_ALL_RES_QP_MAX_OUTST_RECV_WR ; 
 int /*<<< orphan*/  H_ALL_RES_QP_MAX_OUTST_SEND_WR ; 
 int /*<<< orphan*/  H_ALL_RES_QP_MAX_RECV_SGE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_MAX_SEND_SGE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_PTE_PIN ; 
 int /*<<< orphan*/  H_ALL_RES_QP_RESOURCE_TYPE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_RQUEUE_SIZE_PAGES ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SERVICE_TYPE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SIGNALING_TYPE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SMALL_RQ_PAGE_SIZE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SMALL_SQ_PAGE_SIZE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SQUEUE_SIZE_PAGES ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SRQ_LIMIT ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SRQ_QPN ; 
 int /*<<< orphan*/  H_ALL_RES_QP_SRQ_QP_TOKEN ; 
 int /*<<< orphan*/  H_ALL_RES_QP_STORAGE ; 
 int /*<<< orphan*/  H_ALL_RES_QP_UD_AV_LKEY_CTRL ; 
 int /*<<< orphan*/  H_FREE_RESOURCE ; 
 int H_NOT_ENOUGH_RESOURCES ; 
 int H_NO_MEM ; 
 int H_SUCCESS ; 
 int LLQP_RECV_COMP ; 
 int LLQP_SEND_COMP ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int,...) ; 
 int ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hcp_galpas_ctor (int /*<<< orphan*/ *,int,unsigned long,unsigned long) ; 

u64 hipz_h_alloc_resource_qp(const struct ipz_adapter_handle adapter_handle,
			     struct ehca_alloc_qp_parms *parms, int is_user)
{
	int rc;
	u64 ret;
	u64 allocate_controls, max_r10_reg, r11, r12;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	allocate_controls =
		EHCA_BMASK_SET(H_ALL_RES_QP_ENHANCED_OPS, parms->ext_type)
		| EHCA_BMASK_SET(H_ALL_RES_QP_PTE_PIN, 0)
		| EHCA_BMASK_SET(H_ALL_RES_QP_SERVICE_TYPE, parms->servicetype)
		| EHCA_BMASK_SET(H_ALL_RES_QP_SIGNALING_TYPE, parms->sigtype)
		| EHCA_BMASK_SET(H_ALL_RES_QP_STORAGE, parms->qp_storage)
		| EHCA_BMASK_SET(H_ALL_RES_QP_SMALL_SQ_PAGE_SIZE,
				 parms->squeue.page_size)
		| EHCA_BMASK_SET(H_ALL_RES_QP_SMALL_RQ_PAGE_SIZE,
				 parms->rqueue.page_size)
		| EHCA_BMASK_SET(H_ALL_RES_QP_LL_RQ_CQE_POSTING,
				 !!(parms->ll_comp_flags & LLQP_RECV_COMP))
		| EHCA_BMASK_SET(H_ALL_RES_QP_LL_SQ_CQE_POSTING,
				 !!(parms->ll_comp_flags & LLQP_SEND_COMP))
		| EHCA_BMASK_SET(H_ALL_RES_QP_UD_AV_LKEY_CTRL,
				 parms->ud_av_l_key_ctl)
		| EHCA_BMASK_SET(H_ALL_RES_QP_RESOURCE_TYPE, 1);

	max_r10_reg =
		EHCA_BMASK_SET(H_ALL_RES_QP_MAX_OUTST_SEND_WR,
			       parms->squeue.max_wr + 1)
		| EHCA_BMASK_SET(H_ALL_RES_QP_MAX_OUTST_RECV_WR,
				 parms->rqueue.max_wr + 1)
		| EHCA_BMASK_SET(H_ALL_RES_QP_MAX_SEND_SGE,
				 parms->squeue.max_sge)
		| EHCA_BMASK_SET(H_ALL_RES_QP_MAX_RECV_SGE,
				 parms->rqueue.max_sge);

	r11 = EHCA_BMASK_SET(H_ALL_RES_QP_SRQ_QP_TOKEN, parms->srq_token);

	if (parms->ext_type == EQPT_SRQ)
		r12 = EHCA_BMASK_SET(H_ALL_RES_QP_SRQ_LIMIT, parms->srq_limit);
	else
		r12 = EHCA_BMASK_SET(H_ALL_RES_QP_SRQ_QPN, parms->srq_qpn);

	ret = ehca_plpar_hcall9(H_ALLOC_RESOURCE, outs,
				adapter_handle.handle,	           /* r4  */
				allocate_controls,	           /* r5  */
				parms->send_cq_handle.handle,
				parms->recv_cq_handle.handle,
				parms->eq_handle.handle,
				((u64)parms->token << 32) | parms->pd.value,
				max_r10_reg, r11, r12);

	parms->qp_handle.handle = outs[0];
	parms->real_qp_num = (u32)outs[1];
	parms->squeue.act_nr_wqes =
		(u16)EHCA_BMASK_GET(H_ALL_RES_QP_ACT_OUTST_SEND_WR, outs[2]);
	parms->rqueue.act_nr_wqes =
		(u16)EHCA_BMASK_GET(H_ALL_RES_QP_ACT_OUTST_RECV_WR, outs[2]);
	parms->squeue.act_nr_sges =
		(u8)EHCA_BMASK_GET(H_ALL_RES_QP_ACT_SEND_SGE, outs[3]);
	parms->rqueue.act_nr_sges =
		(u8)EHCA_BMASK_GET(H_ALL_RES_QP_ACT_RECV_SGE, outs[3]);
	parms->squeue.queue_size =
		(u32)EHCA_BMASK_GET(H_ALL_RES_QP_SQUEUE_SIZE_PAGES, outs[4]);
	parms->rqueue.queue_size =
		(u32)EHCA_BMASK_GET(H_ALL_RES_QP_RQUEUE_SIZE_PAGES, outs[4]);

	if (ret == H_SUCCESS) {
		rc = hcp_galpas_ctor(&parms->galpas, is_user, outs[6], outs[6]);
		if (rc) {
			ehca_gen_err("Could not establish HW access. rc=%d paddr=%#lx",
				     rc, outs[6]);

			ehca_plpar_hcall_norets(H_FREE_RESOURCE,
						adapter_handle.handle,     /* r4 */
						parms->qp_handle.handle,  /* r5 */
						0, 0, 0, 0, 0);
			ret = H_NO_MEM;
		}
	}

	if (ret == H_NOT_ENOUGH_RESOURCES)
		ehca_gen_err("Not enough resources. ret=%lli", ret);

	return ret;
}