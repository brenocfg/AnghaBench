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
struct rds_ib_mr {int /*<<< orphan*/  sg_dma_len; int /*<<< orphan*/  sg; struct rds_ib_device* device; } ;
struct rds_ib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  ib_dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rds_ib_sync_mr(void *trans_private, int direction)
{
	struct rds_ib_mr *ibmr = trans_private;
	struct rds_ib_device *rds_ibdev = ibmr->device;

	switch (direction) {
	case DMA_FROM_DEVICE:
		ib_dma_sync_sg_for_cpu(rds_ibdev->dev, ibmr->sg,
			ibmr->sg_dma_len, DMA_BIDIRECTIONAL);
		break;
	case DMA_TO_DEVICE:
		ib_dma_sync_sg_for_device(rds_ibdev->dev, ibmr->sg,
			ibmr->sg_dma_len, DMA_BIDIRECTIONAL);
		break;
	}
}