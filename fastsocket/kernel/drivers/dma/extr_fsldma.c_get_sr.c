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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_dma_chan {TYPE_1__* reg_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IN (struct fsl_dma_chan*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 get_sr(struct fsl_dma_chan *fsl_chan)
{
	return DMA_IN(fsl_chan, &fsl_chan->reg_base->sr, 32);
}