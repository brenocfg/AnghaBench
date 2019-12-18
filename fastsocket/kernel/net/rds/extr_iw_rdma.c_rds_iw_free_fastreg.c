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
struct rds_iw_mr_pool {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  dirty_count; int /*<<< orphan*/  free_pinned; int /*<<< orphan*/  dirty_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  dma_len; } ;
struct TYPE_4__ {TYPE_1__ m_sg; int /*<<< orphan*/  m_list; } ;
struct rds_iw_mr {TYPE_2__ mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rds_iw_rdma_fastreg_inv (struct rds_iw_mr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rds_iw_free_fastreg(struct rds_iw_mr_pool *pool,
		struct rds_iw_mr *ibmr)
{
	unsigned long flags;
	int ret;

	if (!ibmr->mapping.m_sg.dma_len)
		return;

	ret = rds_iw_rdma_fastreg_inv(ibmr);
	if (ret)
		return;

	/* Try to post the LOCAL_INV WR to the queue. */
	spin_lock_irqsave(&pool->list_lock, flags);

	list_add_tail(&ibmr->mapping.m_list, &pool->dirty_list);
	atomic_add(ibmr->mapping.m_sg.len, &pool->free_pinned);
	atomic_inc(&pool->dirty_count);

	spin_unlock_irqrestore(&pool->list_lock, flags);
}