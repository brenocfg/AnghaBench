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
struct fsl_dma_chan {TYPE_1__* reg_base; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  cdar; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_OUT (struct fsl_dma_chan*,int /*<<< orphan*/ *,int,int) ; 
 int FSL_DMA_SNEN ; 

__attribute__((used)) static void set_cdar(struct fsl_dma_chan *fsl_chan, dma_addr_t addr)
{
	DMA_OUT(fsl_chan, &fsl_chan->reg_base->cdar, addr | FSL_DMA_SNEN, 64);
}