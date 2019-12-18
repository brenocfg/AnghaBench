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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_dma_ld_hw {int /*<<< orphan*/  count; } ;
struct fsl_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_DMA (struct fsl_dma_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_desc_cnt(struct fsl_dma_chan *fsl_chan,
				struct fsl_dma_ld_hw *hw, u32 count)
{
	hw->count = CPU_TO_DMA(fsl_chan, count, 32);
}