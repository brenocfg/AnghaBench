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
struct dw_dma {int /*<<< orphan*/  all_chan_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  ERROR; int /*<<< orphan*/  DST_TRAN; int /*<<< orphan*/  SRC_TRAN; int /*<<< orphan*/  BLOCK; int /*<<< orphan*/  XFER; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int DW_CFG_DMA_EN ; 
 TYPE_1__ MASK ; 
 int /*<<< orphan*/  channel_clear_bit (struct dw_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writel (struct dw_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_dma_off(struct dw_dma *dw)
{
	dma_writel(dw, CFG, 0);

	channel_clear_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.BLOCK, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.SRC_TRAN, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.DST_TRAN, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.ERROR, dw->all_chan_mask);

	while (dma_readl(dw, CFG) & DW_CFG_DMA_EN)
		cpu_relax();
}