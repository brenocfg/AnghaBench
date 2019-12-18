#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int data; int in_eop; int /*<<< orphan*/  member_0; int /*<<< orphan*/  en; } ;
typedef  TYPE_1__ reg_dma_rw_intr_mask ;
typedef  TYPE_1__ reg_dma_rw_cfg ;
typedef  TYPE_1__ reg_dma_rw_ack_intr ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IRQ ; 
 int /*<<< orphan*/  IN_DMA ; 
 int /*<<< orphan*/  IN_DMA_INST ; 
 int /*<<< orphan*/  OUT_DMA ; 
 int /*<<< orphan*/  OUT_DMA_INST ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  crisv32_free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rw_ack_intr ; 
 int /*<<< orphan*/  rw_cfg ; 
 int /*<<< orphan*/  rw_intr_mask ; 

__attribute__((used)) static void release_cryptocop(void)
{
	unsigned long          flags;
	reg_dma_rw_cfg         dma_cfg = {.en = 0};
	reg_dma_rw_intr_mask   intr_mask_in = {0};
	reg_dma_rw_ack_intr    ack_intr = {.data = 1,.in_eop = 1 };

	local_irq_save(flags);

	/* Clear intr ack. */
	REG_WR(dma, IN_DMA_INST, rw_ack_intr, ack_intr);

	/* Disable DMAs. */
	REG_WR(dma, IN_DMA_INST, rw_cfg, dma_cfg); /* input DMA */
	REG_WR(dma, OUT_DMA_INST, rw_cfg, dma_cfg); /* output DMA */

	/* Disable interrupts. */
	REG_WR(dma, IN_DMA_INST, rw_intr_mask, intr_mask_in);

	local_irq_restore(flags);

	free_irq(DMA_IRQ, NULL);

	(void)crisv32_free_dma(OUT_DMA);
	(void)crisv32_free_dma(IN_DMA);
}