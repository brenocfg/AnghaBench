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
struct i2o_block_request {int /*<<< orphan*/  sg_nents; int /*<<< orphan*/  sg_table; int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int PCI_DMA_FROMDEVICE ; 
 int PCI_DMA_TODEVICE ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i2o_block_sglist_free(struct i2o_block_request *ireq)
{
	enum dma_data_direction direction;

	if (rq_data_dir(ireq->req) == READ)
		direction = PCI_DMA_FROMDEVICE;
	else
		direction = PCI_DMA_TODEVICE;

	dma_unmap_sg(ireq->dev, ireq->sg_table, ireq->sg_nents, direction);
}