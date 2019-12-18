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
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  ndar; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IN (struct fsl_dma_chan*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static dma_addr_t get_ndar(struct fsl_dma_chan *fsl_chan)
{
	return DMA_IN(fsl_chan, &fsl_chan->reg_base->ndar, 64);
}