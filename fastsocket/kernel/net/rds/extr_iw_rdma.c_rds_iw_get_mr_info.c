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
struct rds_iw_mr_pool {int /*<<< orphan*/  max_pages; int /*<<< orphan*/  max_items; } ;
struct rds_iw_device {struct rds_iw_mr_pool* mr_pool; } ;
struct rds_info_rdma_connection {int /*<<< orphan*/  rdma_mr_size; int /*<<< orphan*/  rdma_mr_max; } ;

/* Variables and functions */

void rds_iw_get_mr_info(struct rds_iw_device *rds_iwdev, struct rds_info_rdma_connection *iinfo)
{
	struct rds_iw_mr_pool *pool = rds_iwdev->mr_pool;

	iinfo->rdma_mr_max = pool->max_items;
	iinfo->rdma_mr_size = pool->max_pages;
}