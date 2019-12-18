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
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  DMA_CTRL; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_RX_DMA_EN ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_gbe_enable_dma_rx(struct pch_gbe_hw *hw)
{
	u32 rxdma;

	/* Enables Receive DMA */
	rxdma = ioread32(&hw->reg->DMA_CTRL);
	rxdma |= PCH_GBE_RX_DMA_EN;
	iowrite32(rxdma, &hw->reg->DMA_CTRL);
}