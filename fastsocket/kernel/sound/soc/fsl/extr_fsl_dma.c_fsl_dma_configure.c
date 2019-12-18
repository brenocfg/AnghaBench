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
struct fsl_dma_info {int /*<<< orphan*/ * dma_irq; int /*<<< orphan*/ * dma_channel; int /*<<< orphan*/  ssi_srx_phys; int /*<<< orphan*/  ssi_stx_phys; } ;
struct TYPE_2__ {scalar_t__* assigned; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * dma_channel; int /*<<< orphan*/  ssi_srx_phys; int /*<<< orphan*/  ssi_stx_phys; } ;

/* Variables and functions */
 TYPE_1__ dma_global_data ; 

int fsl_dma_configure(struct fsl_dma_info *dma_info)
{
	static int initialized;

	/* We only support one DMA controller for now */
	if (initialized)
		return 0;

	dma_global_data.ssi_stx_phys = dma_info->ssi_stx_phys;
	dma_global_data.ssi_srx_phys = dma_info->ssi_srx_phys;
	dma_global_data.dma_channel[0] = dma_info->dma_channel[0];
	dma_global_data.dma_channel[1] = dma_info->dma_channel[1];
	dma_global_data.irq[0] = dma_info->dma_irq[0];
	dma_global_data.irq[1] = dma_info->dma_irq[1];
	dma_global_data.assigned[0] = 0;
	dma_global_data.assigned[1] = 0;

	initialized = 1;
	return 1;
}