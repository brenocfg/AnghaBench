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
struct rds_iw_mr_pool {scalar_t__ max_items; int /*<<< orphan*/  item_count; } ;
struct TYPE_2__ {struct rds_iw_mr* m_mr; int /*<<< orphan*/  m_list; int /*<<< orphan*/  m_lock; } ;
struct rds_iw_mr {TYPE_1__ mapping; } ;
struct rds_iw_device {struct rds_iw_mr_pool* mr_pool; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 struct rds_iw_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rds_iw_mr*) ; 
 struct rds_iw_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_destroy_fastreg (struct rds_iw_mr_pool*,struct rds_iw_mr*) ; 
 int /*<<< orphan*/  rds_iw_flush_mr_pool (struct rds_iw_mr_pool*,int /*<<< orphan*/ ) ; 
 int rds_iw_init_fastreg (struct rds_iw_mr_pool*,struct rds_iw_mr*) ; 
 struct rds_iw_mr* rds_iw_reuse_fmr (struct rds_iw_mr_pool*) ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_iw_rdma_mr_alloc ; 
 int /*<<< orphan*/  s_iw_rdma_mr_pool_depleted ; 
 int /*<<< orphan*/  s_iw_rdma_mr_pool_wait ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rds_iw_mr *rds_iw_alloc_mr(struct rds_iw_device *rds_iwdev)
{
	struct rds_iw_mr_pool *pool = rds_iwdev->mr_pool;
	struct rds_iw_mr *ibmr = NULL;
	int err = 0, iter = 0;

	while (1) {
		ibmr = rds_iw_reuse_fmr(pool);
		if (ibmr)
			return ibmr;

		/* No clean MRs - now we have the choice of either
		 * allocating a fresh MR up to the limit imposed by the
		 * driver, or flush any dirty unused MRs.
		 * We try to avoid stalling in the send path if possible,
		 * so we allocate as long as we're allowed to.
		 *
		 * We're fussy with enforcing the FMR limit, though. If the driver
		 * tells us we can't use more than N fmrs, we shouldn't start
		 * arguing with it */
		if (atomic_inc_return(&pool->item_count) <= pool->max_items)
			break;

		atomic_dec(&pool->item_count);

		if (++iter > 2) {
			rds_iw_stats_inc(s_iw_rdma_mr_pool_depleted);
			return ERR_PTR(-EAGAIN);
		}

		/* We do have some empty MRs. Flush them out. */
		rds_iw_stats_inc(s_iw_rdma_mr_pool_wait);
		rds_iw_flush_mr_pool(pool, 0);
	}

	ibmr = kzalloc(sizeof(*ibmr), GFP_KERNEL);
	if (!ibmr) {
		err = -ENOMEM;
		goto out_no_cigar;
	}

	spin_lock_init(&ibmr->mapping.m_lock);
	INIT_LIST_HEAD(&ibmr->mapping.m_list);
	ibmr->mapping.m_mr = ibmr;

	err = rds_iw_init_fastreg(pool, ibmr);
	if (err)
		goto out_no_cigar;

	rds_iw_stats_inc(s_iw_rdma_mr_alloc);
	return ibmr;

out_no_cigar:
	if (ibmr) {
		rds_iw_destroy_fastreg(pool, ibmr);
		kfree(ibmr);
	}
	atomic_dec(&pool->item_count);
	return ERR_PTR(err);
}