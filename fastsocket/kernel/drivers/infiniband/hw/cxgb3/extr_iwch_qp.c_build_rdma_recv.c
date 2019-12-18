#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* pagesz; void** pbl_addr; TYPE_1__* sgl; void* num_sgle; } ;
union t3_wr {TYPE_2__ recv; } ;
typedef  int u8 ;
typedef  unsigned long u32 ;
struct TYPE_9__ {int /*<<< orphan*/  rq_size_log2; int /*<<< orphan*/  rq_wptr; TYPE_3__* rq; } ;
struct iwch_qp {TYPE_4__ wq; int /*<<< orphan*/  rhp; } ;
struct ib_recv_wr {unsigned long num_sge; int /*<<< orphan*/  wr_id; TYPE_5__* sg_list; } ;
struct TYPE_10__ {unsigned long lkey; unsigned long length; scalar_t__ addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  pbl_addr; int /*<<< orphan*/  wr_id; } ;
struct TYPE_6__ {scalar_t__ to; void* len; void* stag; } ;

/* Variables and functions */
 size_t Q_PTR2IDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int T3_MAX_SGE ; 
 void* cpu_to_be32 (unsigned long) ; 
 scalar_t__ cpu_to_be64 (unsigned long) ; 
 int iwch_sgl2pbl_map (int /*<<< orphan*/ ,TYPE_5__*,unsigned long,unsigned long*,int*) ; 

__attribute__((used)) static int build_rdma_recv(struct iwch_qp *qhp, union t3_wr *wqe,
				struct ib_recv_wr *wr)
{
	int i, err = 0;
	u32 pbl_addr[T3_MAX_SGE];
	u8 page_size[T3_MAX_SGE];

	err = iwch_sgl2pbl_map(qhp->rhp, wr->sg_list, wr->num_sge, pbl_addr,
			       page_size);
	if (err)
		return err;
	wqe->recv.pagesz[0] = page_size[0];
	wqe->recv.pagesz[1] = page_size[1];
	wqe->recv.pagesz[2] = page_size[2];
	wqe->recv.pagesz[3] = page_size[3];
	wqe->recv.num_sgle = cpu_to_be32(wr->num_sge);
	for (i = 0; i < wr->num_sge; i++) {
		wqe->recv.sgl[i].stag = cpu_to_be32(wr->sg_list[i].lkey);
		wqe->recv.sgl[i].len = cpu_to_be32(wr->sg_list[i].length);

		/* to in the WQE == the offset into the page */
		wqe->recv.sgl[i].to = cpu_to_be64(((u32)wr->sg_list[i].addr) &
				((1UL << (12 + page_size[i])) - 1));

		/* pbl_addr is the adapters address in the PBL */
		wqe->recv.pbl_addr[i] = cpu_to_be32(pbl_addr[i]);
	}
	for (; i < T3_MAX_SGE; i++) {
		wqe->recv.sgl[i].stag = 0;
		wqe->recv.sgl[i].len = 0;
		wqe->recv.sgl[i].to = 0;
		wqe->recv.pbl_addr[i] = 0;
	}
	qhp->wq.rq[Q_PTR2IDX(qhp->wq.rq_wptr,
			     qhp->wq.rq_size_log2)].wr_id = wr->wr_id;
	qhp->wq.rq[Q_PTR2IDX(qhp->wq.rq_wptr,
			     qhp->wq.rq_size_log2)].pbl_addr = 0;
	return 0;
}