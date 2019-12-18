#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int en; int data; int in_eop; int /*<<< orphan*/  ignore_sync; int /*<<< orphan*/  td3; int /*<<< orphan*/  td2; int /*<<< orphan*/  td1; int /*<<< orphan*/  ipend; } ;
typedef  TYPE_1__ reg_strcop_rw_cfg ;
typedef  TYPE_1__ reg_dma_rw_intr_mask ;
typedef  TYPE_1__ reg_dma_rw_cfg ;
typedef  TYPE_1__ reg_dma_rw_ack_intr ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IRQ ; 
 int /*<<< orphan*/  DMA_PANIC_ON_ERROR ; 
 int /*<<< orphan*/  DMA_WR_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_DMA ; 
 int /*<<< orphan*/  IN_DMA_INST ; 
 int /*<<< orphan*/  OUT_DMA ; 
 int /*<<< orphan*/  OUT_DMA_INST ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  crisv32_request_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_done_interrupt ; 
 int /*<<< orphan*/  dma_strp ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  regi_strcop ; 
 int /*<<< orphan*/  regk_dma_set_w_size4 ; 
 int regk_dma_yes ; 
 int /*<<< orphan*/  regk_strcop_d ; 
 int /*<<< orphan*/  regk_strcop_e ; 
 int /*<<< orphan*/  regk_strcop_little ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_ack_intr ; 
 int /*<<< orphan*/  rw_cfg ; 
 int /*<<< orphan*/  rw_intr_mask ; 
 int /*<<< orphan*/  strcop ; 

__attribute__((used)) static int init_cryptocop(void)
{
	unsigned long          flags;
	reg_dma_rw_cfg         dma_cfg = {.en = 1};
	reg_dma_rw_intr_mask   intr_mask_in = {.data = regk_dma_yes}; /* Only want descriptor interrupts from the DMA in channel. */
	reg_dma_rw_ack_intr    ack_intr = {.data = 1,.in_eop = 1 };
	reg_strcop_rw_cfg      strcop_cfg = {
		.ipend = regk_strcop_little,
		.td1 = regk_strcop_e,
		.td2 = regk_strcop_d,
		.td3 = regk_strcop_e,
		.ignore_sync = 0,
		.en = 1
	};

	if (request_irq(DMA_IRQ, dma_done_interrupt, 0,
			"stream co-processor DMA", NULL))
		panic("request_irq stream co-processor irq dma9");

	(void)crisv32_request_dma(OUT_DMA, "strcop", DMA_PANIC_ON_ERROR,
		0, dma_strp);
	(void)crisv32_request_dma(IN_DMA, "strcop", DMA_PANIC_ON_ERROR,
		0, dma_strp);

	local_irq_save(flags);

	/* Reset and enable the cryptocop. */
	strcop_cfg.en = 0;
	REG_WR(strcop, regi_strcop, rw_cfg, strcop_cfg);
	strcop_cfg.en = 1;
	REG_WR(strcop, regi_strcop, rw_cfg, strcop_cfg);

	/* Enable DMAs. */
	REG_WR(dma, IN_DMA_INST, rw_cfg, dma_cfg); /* input DMA */
	REG_WR(dma, OUT_DMA_INST, rw_cfg, dma_cfg); /* output DMA */

	/* Set up wordsize = 4 for DMAs. */
	DMA_WR_CMD(OUT_DMA_INST, regk_dma_set_w_size4);
	DMA_WR_CMD(IN_DMA_INST, regk_dma_set_w_size4);

	/* Enable interrupts. */
	REG_WR(dma, IN_DMA_INST, rw_intr_mask, intr_mask_in);

	/* Clear intr ack. */
	REG_WR(dma, IN_DMA_INST, rw_ack_intr, ack_intr);

	local_irq_restore(flags);

	return 0;
}