#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct dw_dma {int all_chan_mask; int /*<<< orphan*/  tasklet; TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  ERROR; int /*<<< orphan*/  DST_TRAN; int /*<<< orphan*/  SRC_TRAN; int /*<<< orphan*/  BLOCK; int /*<<< orphan*/  XFER; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_2__ MASK ; 
 int /*<<< orphan*/  STATUS_INT ; 
 int /*<<< orphan*/  channel_clear_bit (struct dw_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t dw_dma_interrupt(int irq, void *dev_id)
{
	struct dw_dma *dw = dev_id;
	u32 status;

	dev_vdbg(dw->dma.dev, "interrupt: status=0x%x\n",
			dma_readl(dw, STATUS_INT));

	/*
	 * Just disable the interrupts. We'll turn them back on in the
	 * softirq handler.
	 */
	channel_clear_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.BLOCK, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.ERROR, dw->all_chan_mask);

	status = dma_readl(dw, STATUS_INT);
	if (status) {
		dev_err(dw->dma.dev,
			"BUG: Unexpected interrupts pending: 0x%x\n",
			status);

		/* Try to recover */
		channel_clear_bit(dw, MASK.XFER, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.BLOCK, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.SRC_TRAN, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.DST_TRAN, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.ERROR, (1 << 8) - 1);
	}

	tasklet_schedule(&dw->tasklet);

	return IRQ_HANDLED;
}