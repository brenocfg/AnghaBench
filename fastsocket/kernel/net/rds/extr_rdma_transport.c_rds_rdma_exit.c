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
 int /*<<< orphan*/  rds_ib_exit () ; 
 int /*<<< orphan*/  rds_iw_exit () ; 
 int /*<<< orphan*/  rds_rdma_listen_stop () ; 

__attribute__((used)) static void rds_rdma_exit(void)
{
	/* stop listening first to ensure no new connections are attempted */
	rds_rdma_listen_stop();
	rds_ib_exit();
	rds_iw_exit();
}