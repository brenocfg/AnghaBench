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
struct TYPE_3__ {int /*<<< orphan*/  dma_len; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ m_sg; } ;
struct rds_iw_mr {TYPE_2__ mapping; struct rds_iw_device* device; } ;
struct rds_iw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  ib_dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rds_iw_sync_mr(void *trans_private, int direction)
{
	struct rds_iw_mr *ibmr = trans_private;
	struct rds_iw_device *rds_iwdev = ibmr->device;

	switch (direction) {
	case DMA_FROM_DEVICE:
		ib_dma_sync_sg_for_cpu(rds_iwdev->dev, ibmr->mapping.m_sg.list,
			ibmr->mapping.m_sg.dma_len, DMA_BIDIRECTIONAL);
		break;
	case DMA_TO_DEVICE:
		ib_dma_sync_sg_for_device(rds_iwdev->dev, ibmr->mapping.m_sg.list,
			ibmr->mapping.m_sg.dma_len, DMA_BIDIRECTIONAL);
		break;
	}
}