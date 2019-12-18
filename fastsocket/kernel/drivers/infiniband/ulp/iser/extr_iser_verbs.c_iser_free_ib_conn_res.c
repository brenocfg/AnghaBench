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
struct iser_cq_desc {int cq_index; } ;
struct iser_conn {scalar_t__ login_buf; scalar_t__ login_resp_dma; TYPE_2__* device; scalar_t__ login_req_dma; scalar_t__ page_vec; TYPE_3__* qp; int /*<<< orphan*/ * fmr_pool; int /*<<< orphan*/  cma_id; } ;
struct TYPE_6__ {TYPE_1__* recv_cq; } ;
struct TYPE_5__ {int /*<<< orphan*/  ib_device; int /*<<< orphan*/ * cq_active_qps; } ;
struct TYPE_4__ {scalar_t__ cq_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISER_RX_LOGIN_SIZE ; 
 int /*<<< orphan*/  ib_destroy_fmr_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_info (char*,struct iser_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  rdma_destroy_qp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iser_free_ib_conn_res(struct iser_conn *ib_conn)
{
	int cq_index;
	BUG_ON(ib_conn == NULL);

	iser_info("freeing conn %p cma_id %p fmr pool %p qp %p\n",
		  ib_conn, ib_conn->cma_id,
		  ib_conn->fmr_pool, ib_conn->qp);

	/* qp is created only once both addr & route are resolved */
	if (ib_conn->fmr_pool != NULL)
		ib_destroy_fmr_pool(ib_conn->fmr_pool);

	if (ib_conn->qp != NULL) {
		cq_index = ((struct iser_cq_desc *)ib_conn->qp->recv_cq->cq_context)->cq_index;
		ib_conn->device->cq_active_qps[cq_index]--;

		rdma_destroy_qp(ib_conn->cma_id);
	}

	ib_conn->fmr_pool = NULL;
	ib_conn->qp	  = NULL;
	kfree(ib_conn->page_vec);

	if (ib_conn->login_buf) {
		if (ib_conn->login_req_dma)
			ib_dma_unmap_single(ib_conn->device->ib_device,
				ib_conn->login_req_dma,
				ISCSI_DEF_MAX_RECV_SEG_LEN, DMA_TO_DEVICE);
		if (ib_conn->login_resp_dma)
			ib_dma_unmap_single(ib_conn->device->ib_device,
				ib_conn->login_resp_dma,
				ISER_RX_LOGIN_SIZE, DMA_FROM_DEVICE);
		kfree(ib_conn->login_buf);
	}

	return 0;
}