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
struct rm_rdma_op {scalar_t__ op_mapped; scalar_t__ op_write; int /*<<< orphan*/  op_nents; int /*<<< orphan*/  op_sg; } ;
struct rds_iw_connection {TYPE_1__* i_cm_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_iw_send_unmap_rdma(struct rds_iw_connection *ic,
				   struct rm_rdma_op *op)
{
	if (op->op_mapped) {
		ib_dma_unmap_sg(ic->i_cm_id->device,
			op->op_sg, op->op_nents,
			op->op_write ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		op->op_mapped = 0;
	}
}