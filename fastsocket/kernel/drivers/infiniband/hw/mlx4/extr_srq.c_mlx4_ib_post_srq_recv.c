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
struct mlx4_wqe_srq_next_seg {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx4_wqe_data_seg {scalar_t__ addr; void* lkey; void* byte_count; } ;
struct TYPE_6__ {void** db; } ;
struct TYPE_5__ {int max_gs; } ;
struct mlx4_ib_srq {size_t head; size_t tail; int wqe_ctr; int /*<<< orphan*/  lock; TYPE_3__ db; TYPE_2__ msrq; int /*<<< orphan*/ * wrid; } ;
struct ib_srq {int dummy; } ;
struct ib_recv_wr {int num_sge; TYPE_1__* sg_list; int /*<<< orphan*/  wr_id; struct ib_recv_wr* next; } ;
struct TYPE_4__ {int length; int lkey; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MLX4_INVALID_LKEY ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct mlx4_wqe_srq_next_seg* get_wqe (struct mlx4_ib_srq*,size_t) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx4_ib_srq* to_msrq (struct ib_srq*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

int mlx4_ib_post_srq_recv(struct ib_srq *ibsrq, struct ib_recv_wr *wr,
			  struct ib_recv_wr **bad_wr)
{
	struct mlx4_ib_srq *srq = to_msrq(ibsrq);
	struct mlx4_wqe_srq_next_seg *next;
	struct mlx4_wqe_data_seg *scat;
	unsigned long flags;
	int err = 0;
	int nreq;
	int i;

	spin_lock_irqsave(&srq->lock, flags);

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (unlikely(wr->num_sge > srq->msrq.max_gs)) {
			err = -EINVAL;
			*bad_wr = wr;
			break;
		}

		if (unlikely(srq->head == srq->tail)) {
			err = -ENOMEM;
			*bad_wr = wr;
			break;
		}

		srq->wrid[srq->head] = wr->wr_id;

		next      = get_wqe(srq, srq->head);
		srq->head = be16_to_cpu(next->next_wqe_index);
		scat      = (struct mlx4_wqe_data_seg *) (next + 1);

		for (i = 0; i < wr->num_sge; ++i) {
			scat[i].byte_count = cpu_to_be32(wr->sg_list[i].length);
			scat[i].lkey       = cpu_to_be32(wr->sg_list[i].lkey);
			scat[i].addr       = cpu_to_be64(wr->sg_list[i].addr);
		}

		if (i < srq->msrq.max_gs) {
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX4_INVALID_LKEY);
			scat[i].addr       = 0;
		}
	}

	if (likely(nreq)) {
		srq->wqe_ctr += nreq;

		/*
		 * Make sure that descriptors are written before
		 * doorbell record.
		 */
		wmb();

		*srq->db.db = cpu_to_be32(srq->wqe_ctr);
	}

	spin_unlock_irqrestore(&srq->lock, flags);

	return err;
}