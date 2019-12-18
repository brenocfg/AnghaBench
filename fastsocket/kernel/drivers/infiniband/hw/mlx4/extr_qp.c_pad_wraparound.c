#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int wqe_cnt; unsigned int wqe_shift; } ;
struct mlx4_ib_qp {unsigned int sq_max_wqes_per_wr; TYPE_1__ sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  post_nop_wqe (struct mlx4_ib_qp*,int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned pad_wraparound(struct mlx4_ib_qp *qp, int ind)
{
	unsigned s = qp->sq.wqe_cnt - (ind & (qp->sq.wqe_cnt - 1));
	if (unlikely(s < qp->sq_max_wqes_per_wr)) {
		post_nop_wqe(qp, ind, s << qp->sq.wqe_shift);
		ind += s;
	}
	return ind;
}