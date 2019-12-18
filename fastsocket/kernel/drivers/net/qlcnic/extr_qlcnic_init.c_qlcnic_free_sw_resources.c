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
struct qlcnic_recv_context {struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_rds_ring {int /*<<< orphan*/ * rx_buf_arr; } ;
struct qlcnic_adapter {int max_rds_rings; struct qlcnic_recv_context* recv_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qlcnic_host_rds_ring*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void qlcnic_free_sw_resources(struct qlcnic_adapter *adapter)
{
	struct qlcnic_recv_context *recv_ctx;
	struct qlcnic_host_rds_ring *rds_ring;
	int ring;

	recv_ctx = adapter->recv_ctx;

	if (recv_ctx->rds_rings == NULL)
		return;

	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &recv_ctx->rds_rings[ring];
		vfree(rds_ring->rx_buf_arr);
		rds_ring->rx_buf_arr = NULL;
	}
	kfree(recv_ctx->rds_rings);
}