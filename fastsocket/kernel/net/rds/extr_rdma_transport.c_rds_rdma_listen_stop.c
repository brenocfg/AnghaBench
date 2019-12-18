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
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rds_rdma_listen_id ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_rdma_listen_stop(void)
{
	if (rds_rdma_listen_id) {
		rdsdebug("cm %p\n", rds_rdma_listen_id);
		rdma_destroy_id(rds_rdma_listen_id);
		rds_rdma_listen_id = NULL;
	}
}