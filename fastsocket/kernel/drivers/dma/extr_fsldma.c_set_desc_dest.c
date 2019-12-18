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
typedef  int u64 ;
struct fsl_dma_ld_hw {int /*<<< orphan*/  dst_addr; } ;
struct fsl_dma_chan {int feature; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_DMA (struct fsl_dma_chan*,int,int) ; 
 scalar_t__ FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE ; 
 int FSL_DMA_IP_85XX ; 
 int FSL_DMA_IP_MASK ; 

__attribute__((used)) static void set_desc_dest(struct fsl_dma_chan *fsl_chan,
				struct fsl_dma_ld_hw *hw, dma_addr_t dest)
{
	u64 snoop_bits;

	snoop_bits = ((fsl_chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_85XX)
		? ((u64)FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE << 32) : 0;
	hw->dst_addr = CPU_TO_DMA(fsl_chan, snoop_bits | dest, 64);
}