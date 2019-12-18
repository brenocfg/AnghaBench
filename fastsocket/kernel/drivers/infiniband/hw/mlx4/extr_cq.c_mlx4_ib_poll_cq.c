#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx4_ib_qp {int dummy; } ;
struct mlx4_ib_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  mcq; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  mlx4_cq_set_ci (int /*<<< orphan*/ *) ; 
 int mlx4_ib_poll_one (struct mlx4_ib_cq*,struct mlx4_ib_qp**,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx4_ib_cq* to_mcq (struct ib_cq*) ; 

int mlx4_ib_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct mlx4_ib_cq *cq = to_mcq(ibcq);
	struct mlx4_ib_qp *cur_qp = NULL;
	unsigned long flags;
	int npolled;
	int err = 0;

	spin_lock_irqsave(&cq->lock, flags);

	for (npolled = 0; npolled < num_entries; ++npolled) {
		err = mlx4_ib_poll_one(cq, &cur_qp, wc + npolled);
		if (err)
			break;
	}

	mlx4_cq_set_ci(&cq->mcq);

	spin_unlock_irqrestore(&cq->lock, flags);

	if (err == 0 || err == -EAGAIN)
		return npolled;
	else
		return err;
}