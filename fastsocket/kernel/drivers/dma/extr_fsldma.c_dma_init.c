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
struct fsl_dma_chan {int feature; TYPE_1__* reg_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_OUT (struct fsl_dma_chan*,int /*<<< orphan*/ *,int,int) ; 
#define  FSL_DMA_IP_83XX 129 
#define  FSL_DMA_IP_85XX 128 
 int FSL_DMA_IP_MASK ; 
 int FSL_DMA_MR_EIE ; 
 int FSL_DMA_MR_EOLNIE ; 
 int FSL_DMA_MR_EOSIE ; 
 int FSL_DMA_MR_EOTIE ; 
 int FSL_DMA_MR_PRC_RM ; 

__attribute__((used)) static void dma_init(struct fsl_dma_chan *fsl_chan)
{
	/* Reset the channel */
	DMA_OUT(fsl_chan, &fsl_chan->reg_base->mr, 0, 32);

	switch (fsl_chan->feature & FSL_DMA_IP_MASK) {
	case FSL_DMA_IP_85XX:
		/* Set the channel to below modes:
		 * EIE - Error interrupt enable
		 * EOSIE - End of segments interrupt enable (basic mode)
		 * EOLNIE - End of links interrupt enable
		 */
		DMA_OUT(fsl_chan, &fsl_chan->reg_base->mr, FSL_DMA_MR_EIE
				| FSL_DMA_MR_EOLNIE | FSL_DMA_MR_EOSIE, 32);
		break;
	case FSL_DMA_IP_83XX:
		/* Set the channel to below modes:
		 * EOTIE - End-of-transfer interrupt enable
		 * PRC_RM - PCI read multiple
		 */
		DMA_OUT(fsl_chan, &fsl_chan->reg_base->mr, FSL_DMA_MR_EOTIE
				| FSL_DMA_MR_PRC_RM, 32);
		break;
	}

}