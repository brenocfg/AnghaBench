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

/* Variables and functions */
 int rds_ib_init () ; 
 int /*<<< orphan*/  rds_iw_exit () ; 
 int rds_iw_init () ; 
 int rds_rdma_listen_init () ; 
 int /*<<< orphan*/  rds_rdma_listen_stop () ; 

__attribute__((used)) static int rds_rdma_init(void)
{
	int ret;

	ret = rds_rdma_listen_init();
	if (ret)
		goto out;

	ret = rds_iw_init();
	if (ret)
		goto err_iw_init;

	ret = rds_ib_init();
	if (ret)
		goto err_ib_init;

	goto out;

err_ib_init:
	rds_iw_exit();
err_iw_init:
	rds_rdma_listen_stop();
out:
	return ret;
}