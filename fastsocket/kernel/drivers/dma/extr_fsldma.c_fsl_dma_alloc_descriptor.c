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
struct fsl_dma_chan {int /*<<< orphan*/  common; int /*<<< orphan*/  desc_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  tx_submit; } ;
struct fsl_desc_sw {TYPE_1__ async_tx; int /*<<< orphan*/  tx_list; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct fsl_desc_sw* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_dma_tx_submit ; 
 int /*<<< orphan*/  memset (struct fsl_desc_sw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct fsl_desc_sw *fsl_dma_alloc_descriptor(
					struct fsl_dma_chan *fsl_chan)
{
	dma_addr_t pdesc;
	struct fsl_desc_sw *desc_sw;

	desc_sw = dma_pool_alloc(fsl_chan->desc_pool, GFP_ATOMIC, &pdesc);
	if (desc_sw) {
		memset(desc_sw, 0, sizeof(struct fsl_desc_sw));
		INIT_LIST_HEAD(&desc_sw->tx_list);
		dma_async_tx_descriptor_init(&desc_sw->async_tx,
						&fsl_chan->common);
		desc_sw->async_tx.tx_submit = fsl_dma_tx_submit;
		desc_sw->async_tx.phys = pdesc;
	}

	return desc_sw;
}