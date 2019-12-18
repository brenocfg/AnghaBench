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
struct TYPE_2__ {int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_IN (struct fsl_dma_chan*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DMA_OUT (struct fsl_dma_chan*,int /*<<< orphan*/ *,int,int) ; 
 int __ilog2 (int) ; 

__attribute__((used)) static void fsl_chan_set_request_count(struct fsl_dma_chan *fsl_chan, int size)
{
	BUG_ON(size > 1024);
	DMA_OUT(fsl_chan, &fsl_chan->reg_base->mr,
		DMA_IN(fsl_chan, &fsl_chan->reg_base->mr, 32)
			| ((__ilog2(size) << 24) & 0x0f000000),
		32);
}