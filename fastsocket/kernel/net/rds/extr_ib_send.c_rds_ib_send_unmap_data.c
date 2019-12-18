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
struct rm_data_op {scalar_t__ op_nents; int /*<<< orphan*/  op_sg; } ;
struct rds_ib_connection {TYPE_1__* i_cm_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_ib_send_unmap_data(struct rds_ib_connection *ic,
				   struct rm_data_op *op,
				   int wc_status)
{
	if (op->op_nents)
		ib_dma_unmap_sg(ic->i_cm_id->device,
				op->op_sg, op->op_nents,
				DMA_TO_DEVICE);
}